#include "IEECS.h"
#include "GameStartEvent.h"
#include "IEECSInputSystem.h"

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
    entityManager->remove(entity);

    // TODO remove children entities
    // TODO remove entity from components

    emit entityRemoved(entity);
}

int IEECS::attachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!entityManager->attachComponent(entity, (unsigned long long)type))
        return -1;

    // TODO get system and then attach

    switch(type)
    {
    case IEComponentType::Input: { return -1; }
    case IEComponentType::Transform: { return -1; }
    case IEComponentType::Camera: { return -1; }
    case IEComponentType::CameraController: { return -1; }
    case IEComponentType::Material: { return -1; }
    case IEComponentType::Mesh: { return -1; }
    case IEComponentType::Shader: { return -1; }
    case IEComponentType::Renderable: { return -1; }
    case IEComponentType::Physics: { return -1; }
    case IEComponentType::ParentChild: { return -1; }
    default: { return -1; }
    }
}

bool IEECS::detachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!entityManager->detachComponent(entity, (unsigned long long)type))
        return false;

    // TODO get system and then detach

    switch(type)
    {
    case IEComponentType::Input: { return true; }
    case IEComponentType::Transform: { return true; }
    case IEComponentType::Camera: { return true; }
    case IEComponentType::CameraController: { return true; }
    case IEComponentType::Material: { return true; }
    case IEComponentType::Mesh: { return true; }
    case IEComponentType::Shader: { return true; }
    case IEComponentType::Renderable: { return true; }
    case IEComponentType::Physics: { return true; }
    case IEComponentType::ParentChild: { return true; }
    default: { return false; }
    }
}

bool IEECS::hasComponent(const IEEntity entity, const IEComponentType type)
{
    return entityManager->hasComponent(entity, (unsigned long long)type);
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

QDataStream& operator<<(QDataStream& out, const IEECS& ecs)
{
    out << *ecs.getEntityManager();
    out << (int)ecs.getSystems().size();

    QMapIterator<IEComponentType, IEECSSystem*> it(ecs.getSystems());
    while(it.hasNext())
    {
        it.next();

        out << it.key();

        switch(it.key())
        {
        case IEComponentType::Input: { out << *static_cast<IEECSInputSystem*>(it.value()); break; }
        case IEComponentType::Transform: { break; }
        case IEComponentType::Camera: { break; }
        case IEComponentType::CameraController: { break; }
        case IEComponentType::Material: { break; }
        case IEComponentType::Mesh: { break; }
        case IEComponentType::Shader: { break; }
        case IEComponentType::Renderable: { break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::ParentChild: { break; }
        default: { break; }
        }
    }

    return out;
}

QDataStream& operator>>(QDataStream& in, IEECS& ecs)
{
    IEEntityManager* entityManager = ecs.getEntityManager();
    QMap<IEComponentType, IEECSSystem*> tempSystems = ecs.getSystems();
    int size = 0;

    in >> *entityManager >> size;

    IEComponentType type;
    for(int i = 0; i < size; i++)
    {
        in >> type;

        switch(type)
        {
        case IEComponentType::Input: { in >> *static_cast<IEECSInputSystem*>(tempSystems[type]); break; }
        case IEComponentType::Transform: { break; }
        case IEComponentType::Camera: { break; }
        case IEComponentType::CameraController: { break; }
        case IEComponentType::Material: { break; }
        case IEComponentType::Mesh: { break; }
        case IEComponentType::Shader: { break; }
        case IEComponentType::Renderable: { break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::ParentChild: { break; }
        default: { break; }
        }
    }

    ecs.setEntityManager(entityManager);
    ecs.setSystems(tempSystems);

    return in;
}
