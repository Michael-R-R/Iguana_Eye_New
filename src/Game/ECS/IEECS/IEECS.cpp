#include "IEECS.h"
#include "GameStartEvent.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

IEECS::IEECS() :
    IEObject(),
    onUpdateEvent(nullptr),
    entityManager(std::make_unique<IEEntityManager>()),
    systems()
{
    initSystems();
}

IEECS::~IEECS()
{

}

void IEECS::startup(const GameStartEvent& event)
{
    for(auto& i : systems)
    {
        i.second->startup(event);
    }
}

void IEECS::shutdown()
{
    clearSystems();
}

void IEECS::onUpdateFrame()
{
    for(auto& i : systems)
    {
        i.second->onUpdateFrame(&(*onUpdateEvent));
    }
}

IEEntity IEECS::create()
{
    IEEntity entity = entityManager->create();

    this->attachComponent(entity, "Name");
    this->attachComponent(entity, "Hierarchy");
    this->attachComponent(entity, "Transform");

    emit entityCreated(entity);

    return entity;
}

void IEECS::remove(const IEEntity entity)
{
    // Recursively remove child entities
    auto* hierarchySystem = getComponent<IEECSHierarchySystem>("Hierarchy");
    int hierarchyIndex = hierarchySystem->lookUpIndex(entity);
    auto childrenList = hierarchySystem->getChildrenList(hierarchyIndex);
    for(auto& child : childrenList)
    {
        this->remove(child);
    }

    // Iterate through the systems, removing the entity from them
    for(auto& i : systems)
    {
        detachComponent(entity, i.first);
    }

    entityManager->remove(entity);

    emit entityRemoved(entity);
}

int IEECS::attachComponent(const IEEntity entity, const QString& component)
{
    if(!doesSystemExist(component))
        return -1;

    if(!entityManager->attachComponent(entity, component))
        return -1;

    emit componentAttached(entity, component);

    return systems[component]->attach(entity);
}

bool IEECS::detachComponent(const IEEntity entity, const QString& component)
{
    if(!doesSystemExist(component))
        return false;

    if(!entityManager->detachComponent(entity, component))
        return false;

    emit componentDetached(entity, component);

    return systems[component]->detach(entity);
}

bool IEECS::hasComponent(const IEEntity entity, const QString& component) const
{
    return entityManager->hasComponent(entity, component);
}

bool IEECS::doesSystemExist(const QString& component) const
{
    return (systems.find(component) != systems.end());
}

int IEECS::entityCount() const
{
    return entityManager->count();
}

void IEECS::clearSystems()
{
    systems.clear();
}

void IEECS::initSystems()
{
    auto nameSystem = std::make_unique<IEECSNameSystem>();
    auto hierarchySystem = std::make_unique<IEECSHierarchySystem>();
    auto inputSystem = std::make_unique<IEECSInputSystem>();
    auto scriptSystem = std::make_unique<IEECSScriptSystem>();
    auto rigidbody3dSystem = std::make_unique<IEECSRigidbody3DSystem>();
    auto transformSystem = std::make_unique<IEECSTransformSystem>();
    auto cameraSystem = std::make_unique<IEECSCameraSystem>();
    auto meshSystem = std::make_unique<IEECSMeshSystem>();
    auto materialSystem = std::make_unique<IEECSMaterialSystem>();
    auto shaderSystem = std::make_unique<IEECSShaderSystem>();
    auto renderableSystem = std::make_unique<IEECSRenderableSystem>();

    systems["Name"] = std::move(nameSystem);
    systems["Hierarchy"] = std::move(hierarchySystem);
    systems["Input"] = std::move(inputSystem);
    systems["Script"] = std::move(scriptSystem);
    systems["Rigidbody3D"] = std::move(rigidbody3dSystem);
    systems["Transform"] = std::move(transformSystem);
    systems["Camera"] = std::move(cameraSystem);
    systems["Mesh"] = std::move(meshSystem);
    systems["Material"] = std::move(materialSystem);
    systems["Shader"] = std::move(shaderSystem);
    systems["Renderable"] = std::move(renderableSystem);
}

QDataStream& IEECS::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& ecs = static_cast<const IEECS&>(obj);

    out << *ecs.entityManager;

    for(auto& i : ecs.systems)
    {
        out << *i.second;
    }

    return out;
}

QDataStream& IEECS::deserialize(QDataStream& in, Serializable& obj)
{
    auto& ecs = static_cast<IEECS&>(obj);

    in >> *ecs.entityManager;

    for(auto& i : ecs.systems)
    {
        in >> *i.second;
    }

    return in;
}
