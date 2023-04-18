#include "IEECS.h"
#include "IEGame.h"
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

IEECS::IEECS(QObject* parent) :
    IEGameSystem(parent),
    systems(),
    entityManager(new IEEntityManager(this))
{

}

IEECS::~IEECS()
{

}

void IEECS::startup(IEGame&)
{
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

void IEECS::onUpdateFrame(ECSOnUpdateEvent& event)
{
    for(auto& i : systems)
    {
        i->onUpdateFrame(event);
    }
}

IEEntity IEECS::create()
{
    IEEntity entity = entityManager->create();

    this->attachComponent<IEECSNameSystem>(entity);
    this->attachComponent<IEECSHierarchySystem>(entity);
    this->attachComponent<IEECSTransformSystem>(entity);

    emit entityCreated(entity);

    return entity;
}

void IEECS::remove(const IEEntity entity)
{
    // Recursively remove child entities
    auto* hierarchySystem = getComponent<IEECSHierarchySystem>();
    int hierarchyIndex = hierarchySystem->lookUpIndex(entity);
    auto childrenList = hierarchySystem->getChildrenList(hierarchyIndex);
    for(auto& child : childrenList)
    {
        this->remove(child);
    }

    // Iterate through the systems, removing the entity from them
    QMapIterator<size_t, IEECSSystem*> it(systems);
    while(it.hasNext())
    {
        it.next();
        detachComponent(entity, it.key());
    }

    entityManager->remove(entity);

    emit entityRemoved(entity);
}

int IEECS::entityCount() const
{
    return entityManager->count();
}

void IEECS::clearSystems()
{
    for(auto* i : systems)
    {
        delete i;
    }

    systems.clear();
}

void IEECS::initSystems()
{
    systems[typeid(IEECSNameSystem).hash_code()] = new IEECSNameSystem(this);
    systems[typeid(IEECSHierarchySystem).hash_code()] = new IEECSHierarchySystem(this);
    systems[typeid(IEECSInputSystem).hash_code()] = new IEECSInputSystem(this);
    systems[typeid(IEECSScriptSystem).hash_code()] = new IEECSScriptSystem(this);
    systems[typeid(IEECSColliderSystem).hash_code()] = new IEECSColliderSystem(this);
    systems[typeid(IEECSRigidbody3DSystem).hash_code()] = new IEECSRigidbody3DSystem(this);
    systems[typeid(IEECSTransformSystem).hash_code()] = new IEECSTransformSystem(this);
    systems[typeid(IEECSCameraSystem).hash_code()] = new IEECSCameraSystem(this);
    systems[typeid(IEECSMeshSystem).hash_code()] = new IEECSMeshSystem(this);
    systems[typeid(IEECSMaterialSystem).hash_code()] = new IEECSMaterialSystem(this);
    systems[typeid(IEECSShaderSystem).hash_code()] = new IEECSShaderSystem(this);
    systems[typeid(IEECSRenderableSystem).hash_code()] = new IEECSRenderableSystem(this);
}

bool IEECS::detachComponent(const IEEntity entity, const size_t& component)
{
    if(!doesSystemExist(component))
        return false;

    if(!entityManager->detachComponent(entity, component))
        return false;

    emit componentDetached(entity, component);

    return systems[component]->detach(entity);
}

bool IEECS::doesSystemExist(const size_t& val) const
{
    return systems.contains(val);
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
