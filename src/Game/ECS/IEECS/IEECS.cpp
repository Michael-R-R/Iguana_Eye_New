#include "IEECS.h"
#include "GameStartEvent.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

IEECS::IEECS() :
    IEObject(),
    entityManager(std::make_unique<IEEntityManager>()),
    systems(),
    onUpdateEvent(nullptr)
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

    onUpdateEvent = std::make_unique<ECSOnUpdateEvent>(this);

    // TODO test
    auto* scriptSystem = this->getComponent<IEECSScriptSystem>(IEComponentType::Script);
    IEEntity entity = this->create();
    int index = this->attachComponent(entity, IEComponentType::Script);
    scriptSystem->addScript(index, IEEntityScript("./resources/scripts/test/test1.lua", 1));
    scriptSystem->initalizeScript(index, 1);
    scriptSystem->startScript(index, 1);
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

    this->attachComponent(entity, IEComponentType::Name);
    this->attachComponent(entity, IEComponentType::Hierarchy);
    this->attachComponent(entity, IEComponentType::Transform);

    emit entityCreated(entity);

    return entity;
}

void IEECS::remove(const IEEntity entity)
{
    // Recursively remove child entities
    auto* hierarchySystem = getComponent<IEECSHierarchySystem>(IEComponentType::Hierarchy);
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

int IEECS::attachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!doesSystemExist(type))
        return -1;

    if(!entityManager->attachComponent(entity, (unsigned long long)type))
        return -1;

    return systems[type]->attach(entity);
}

bool IEECS::detachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!doesSystemExist(type))
        return false;

    if(!entityManager->detachComponent(entity, (unsigned long long)type))
        return false;

    return systems[type]->detach(entity);
}

bool IEECS::hasComponent(const IEEntity entity, const IEComponentType type) const
{
    return entityManager->hasComponent(entity, (unsigned long long)type);
}

bool IEECS::doesSystemExist(const IEComponentType type) const
{
    return (systems.find(type) != systems.end());
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
    auto transformSystem = std::make_unique<IEECSTransformSystem>();
    auto cameraSystem = std::make_unique<IEECSCameraSystem>();
    auto meshSystem = std::make_unique<IEECSMeshSystem>();
    auto materialSystem = std::make_unique<IEECSMaterialSystem>();
    auto shaderSystem = std::make_unique<IEECSShaderSystem>();
    auto renderableSystem = std::make_unique<IEECSRenderableSystem>();

    systems[IEComponentType::Name] = std::move(nameSystem);
    systems[IEComponentType::Hierarchy] = std::move(hierarchySystem);
    systems[IEComponentType::Input] = std::move(inputSystem);
    systems[IEComponentType::Script] = std::move(scriptSystem);
    systems[IEComponentType::Transform] = std::move(transformSystem);
    systems[IEComponentType::Camera] = std::move(cameraSystem);
    systems[IEComponentType::Mesh] = std::move(meshSystem);
    systems[IEComponentType::Material] = std::move(materialSystem);
    systems[IEComponentType::Shader] = std::move(shaderSystem);
    systems[IEComponentType::Renderable] = std::move(renderableSystem);
}

QDataStream& IEECS::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& ecs = static_cast<const IEECS&>(obj);

    out << *ecs.entityManager << (int)ecs.systems.size();

    for(auto& i : ecs.systems)
    {
        out << i.first;

        auto* value = &(*i.second);

        switch(i.first)
        {
        case IEComponentType::Name: { out << *static_cast<IEECSNameSystem*>(value); break; }
        case IEComponentType::Hierarchy: { out << *static_cast<IEECSHierarchySystem*>(value); break; }
        case IEComponentType::Input: { out << *static_cast<IEECSInputSystem*>(value); break; }
        case IEComponentType::Script: { out << *static_cast<IEECSScriptSystem*>(value); break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::Transform: { out << *static_cast<IEECSTransformSystem*>(value); break; }
        case IEComponentType::Camera: { out << *static_cast<IEECSCameraSystem*>(value); break; }
        case IEComponentType::Material: { out << *static_cast<IEECSMaterialSystem*>(value); break; }
        case IEComponentType::Mesh: { out << *static_cast<IEECSMeshSystem*>(value); break; }
        case IEComponentType::Shader: { out << *static_cast<IEECSShaderSystem*>(value); break; }
        case IEComponentType::Renderable: { out << *static_cast<IEECSRenderableSystem*>(value); break; }
        default: { break; }
        }
    }

    return out;
}

QDataStream& IEECS::deserialize(QDataStream& in, Serializable& obj)
{
    auto& ecs = static_cast<IEECS&>(obj);

    int size = 0;
    in >> *ecs.entityManager >> size;

    IEComponentType type;
    for(int i = 0; i < size; i++)
    {
        in >> type;

        auto* value = &(*ecs.systems.at(type));

        switch(type)
        {
        case IEComponentType::Name: { in >> *static_cast<IEECSNameSystem*>(value); break; }
        case IEComponentType::Hierarchy: { in >> *static_cast<IEECSHierarchySystem*>(value); break; }
        case IEComponentType::Input: { in >> *static_cast<IEECSInputSystem*>(value); break; }
        case IEComponentType::Script: { in >> *static_cast<IEECSScriptSystem*>(value); break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::Transform: { in >> *static_cast<IEECSTransformSystem*>(value); break; }
        case IEComponentType::Camera: { in >> *static_cast<IEECSCameraSystem*>(value); break; }
        case IEComponentType::Material: { in >> *static_cast<IEECSMaterialSystem*>(value); break; }
        case IEComponentType::Mesh: { in >> *static_cast<IEECSMeshSystem*>(value); break; }
        case IEComponentType::Shader: { in >> *static_cast<IEECSShaderSystem*>(value); break; }
        case IEComponentType::Renderable: { in >> *static_cast<IEECSRenderableSystem*>(value); break; }
        default: { break; }
        }
    }

    return in;
}
