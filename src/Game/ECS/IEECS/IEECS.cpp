#include "IEECS.h"

IEECS::IEECS(QObject* parent) :
    IEObject(parent),
    entityManager(new IEEntityManager())
{

}

IEECS::~IEECS()
{
    delete entityManager;
}

void IEECS::startup()
{

}

void IEECS::shutdown()
{

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
    case IEComponentType::Name: { return -1; }
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
    case IEComponentType::Name: { return true; }
    case IEComponentType::ParentChild: { return true; }
    default: { return false; }
    }
}

bool IEECS::hasComponent(const IEEntity entity, const IEComponentType type)
{
    return entityManager->hasComponent(entity, (unsigned long long)type);
}

QDataStream& operator<<(QDataStream& out, const IEECS& ecs)
{
    out << *ecs.getEntityManager();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEECS& ecs)
{
    IEEntityManager* entityManager = ecs.getEntityManager();

    in >> *entityManager;

    ecs.setEntityManager(entityManager);

    return in;
}
