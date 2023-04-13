#include "IEECS.h"
#include "IEGame.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSColliderSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"

IEECS::IEECS() :
    systems(),
    entityManager(nullptr)
{

}

IEECS::~IEECS()
{

}

void IEECS::startup(IEGame&)
{
    entityManager = QSharedPointer<IEEntityManager>::create();
    initSystems();
}

void IEECS::shutdown(IEGame&)
{
    entityManager = nullptr;
    clearSystems();
}

void IEECS::initalize(IEGame&)
{
    for(auto& i : systems)
    {
        i->initalize();
    }
}

void IEECS::reset(IEGame&)
{
    for(auto& i : systems)
    {
        i->reset();
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
    QMapIterator<QString, QSharedPointer<IEECSSystem>> it(systems);
    while(it.hasNext())
    {
        it.next();
        detachComponent(entity, it.key());
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
    auto nameSystem = QSharedPointer<IEECSNameSystem>::create();
    auto hierarchySystem = QSharedPointer<IEECSHierarchySystem>::create();
    auto inputSystem = QSharedPointer<IEECSInputSystem>::create();
    auto scriptSystem = QSharedPointer<IEECSScriptSystem>::create();
    auto colliderSystem = QSharedPointer<IEECSColliderSystem>::create();
    auto rigidbody3dSystem = QSharedPointer<IEECSRigidbody3DSystem>::create();
    auto transformSystem = QSharedPointer<IEECSTransformSystem>::create();
    auto cameraSystem = QSharedPointer<IEECSCameraSystem>::create();
    auto meshSystem = QSharedPointer<IEECSMeshSystem>::create();
    auto materialSystem = QSharedPointer<IEECSMaterialSystem>::create();
    auto shaderSystem = QSharedPointer<IEECSShaderSystem>::create();
    auto renderableSystem = QSharedPointer<IEECSRenderableSystem>::create();

    systems["Name"] = nameSystem;
    systems["Hierarchy"] = hierarchySystem;
    systems["Input"] = inputSystem;
    systems["Script"] = scriptSystem;
    systems["Collider"] = colliderSystem;
    systems["Rigidbody3D"] = rigidbody3dSystem;
    systems["Transform"] = transformSystem;
    systems["Camera"] = cameraSystem;
    systems["Mesh"] = meshSystem;
    systems["Material"] = materialSystem;
    systems["Shader"] = shaderSystem;
    systems["Renderable"] = renderableSystem;
}

QDataStream& IEECS::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& ecs = static_cast<const IEECS&>(obj);

    out << *ecs.entityManager;

    for(auto& i : ecs.systems)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEECS::deserialize(QDataStream& in, Serializable& obj)
{
    auto& ecs = static_cast<IEECS&>(obj);

    in >> *ecs.entityManager;

    for(auto& i : ecs.systems)
    {
        in >> *i;
    }

    return in;
}
