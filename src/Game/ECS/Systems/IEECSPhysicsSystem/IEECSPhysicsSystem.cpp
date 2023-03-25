#include "IEECSPhysicsSystem.h"

IEECSPhysicsSystem::IEECSPhysicsSystem() :
    data()
{

}

IEECSPhysicsSystem::~IEECSPhysicsSystem()
{

}

void IEECSPhysicsSystem::startup(const GameStartEvent&)
{
    // Not used
}

int IEECSPhysicsSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.push_back(entity);

    return index;
}

bool IEECSPhysicsSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSPhysicsSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QDataStream& IEECSPhysicsSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSPhysicsSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSPhysicsSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSPhysicsSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
