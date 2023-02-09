#include "IEECS.h"
#include "GameStartEvent.h"

IEECS::IEECS(QObject* parent) :
    IEObject(parent),
    entityManager(new IEEntityManager()),
    systems()
{
    initSystems();
}

IEECS::~IEECS()
{
    delete entityManager;
    clearSystems();
}

void IEECS::startup(const GameStartEvent&)
{

}

void IEECS::shutdown()
{
    clearSystems();
}

IEEntity IEECS::create()
{
    IEEntity entity = entityManager->create();

    emit entityCreated(entity);

    return entity;
}

void IEECS::remove(const IEEntity entity)
{
    // TODO remove children entities
    QMapIterator<IEComponentType, IEECSSystem*> it(systems);
    while(it.hasNext())
    {
        it.next();

        detachComponent(entity, it.key());
    }

    entityManager->remove(entity);

    emit entityRemoved(entity);
}

int IEECS::attachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!entityManager->attachComponent(entity, (unsigned long long)type))
        return -1;

    if(!doesSystemExist(type))
        return false;

    return systems[type]->attach(entity);
}

bool IEECS::detachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!entityManager->detachComponent(entity, (unsigned long long)type))
        return false;

    if(!doesSystemExist(type))
        return false;

    return systems[type]->detach(entity);
}

bool IEECS::hasComponent(const IEEntity entity, const IEComponentType type)
{
    return entityManager->hasComponent(entity, (unsigned long long)type);
}

bool IEECS::doesSystemExist(const IEComponentType type)
{
    return systems.contains(type);
}

void IEECS::clearSystems()
{
    QMapIterator<IEComponentType, IEECSSystem*> it(systems);
    while(it.hasNext())
    {
        it.next();

        IEECSSystem* temp = it.value();
        systems[it.key()] = nullptr;
        delete temp;
    }

    systems.clear();
}

void IEECS::initSystems()
{
    auto inputSystem = new IEECSInputSystem();

    systems[IEComponentType::Input] = inputSystem;
}
