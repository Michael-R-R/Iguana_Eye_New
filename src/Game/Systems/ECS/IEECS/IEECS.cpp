#include "IEECS.h"
#include "IEGame.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
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
    systems(), systemIndex(),
    entityManager(new IEEntityManager(this))
{

}

IEECS::~IEECS()
{

}

void IEECS::startup(IEGame& game)
{
    appendSystem(new IEECSNameSystem(this));
    appendSystem(new IEECSHierarchySystem(this));
    appendSystem(new IEECSScriptSystem(this));
    appendSystem(new IEECSColliderSystem(this));
    appendSystem(new IEECSRigidbody3DSystem(this));
    appendSystem(new IEECSTransformSystem(this));
    appendSystem(new IEECSCameraSystem(this));
    appendSystem(new IEECSMeshSystem(this));
    appendSystem(new IEECSMaterialSystem(this));
    appendSystem(new IEECSShaderSystem(this));
    appendSystem(new IEECSRenderableSystem(this));

    foreach (auto* i, qAsConst(systems))
    {
        i->startUp(game);
    }
}

void IEECS::shutdown(IEGame& game)
{
    for(int i = systems.size() - 1; i >= 0; i--)
    {
        systems[i]->shutdown(game);
    }
    clearSystems();

    delete entityManager;
    entityManager = nullptr;
}

void IEECS::onSerialize(IEGame& game)
{
    foreach (auto* i, qAsConst(systems))
    {
        i->onSerialize(game);
    }
}

void IEECS::onDeserialize(IEGame& game)
{
    foreach (auto* i, qAsConst(systems))
    {
        i->onDeserialize(game);
    }
}

void IEECS::onUpdateFrame()
{
    for(auto* i : qAsConst(systems))
    {
        i->onUpdateFrame();
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
    for(int i = 0; i < systems.size(); i++)
    {
        detachComponent(entity, systems[i]->getID());
    }

    entityManager->remove(entity);

    emit entityRemoved(entity);
}

int IEECS::entityCount() const
{
    return entityManager->count();
}

bool IEECS::appendSystem(IEECSSystem* system)
{
    if(!system || doesSystemExist(system->getID()))
        return false;

    const int index = systems.size();
    systems.append(system);
    systemIndex.insert(system->getID(), index);

    return true;
}

void IEECS::clearSystems()
{
    for(auto* i : qAsConst(systems))
    {
        delete i;
        i = nullptr;
    }

    systems.clear();
    systemIndex.clear();
}

bool IEECS::detachComponent(const IEEntity entity, const size_t& component)
{
    if(!doesSystemExist(component))
        return false;

    if(!entityManager->detachComponent(entity, component))
        return false;

    emit componentDetached(entity, component);

    return systems[systemIndex[component]]->detach(entity);
}

bool IEECS::doesSystemExist(const size_t& val) const
{
    return systemIndex.contains(val);
}

QDataStream& IEECS::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& ecs = static_cast<const IEECS&>(obj);

    for(auto& i : qAsConst(ecs.systems))
    {
        out << *i;
    }

    out << ecs.systemIndex << *ecs.entityManager;


    return out;
}

QDataStream& IEECS::deserialize(QDataStream& in, Serializable& obj)
{
    auto& ecs = static_cast<IEECS&>(obj);

    for(auto& i : qAsConst(ecs.systems))
    {
        in >> *i;
    }

    in >> ecs.systemIndex >> *ecs.entityManager;

    return in;
}
