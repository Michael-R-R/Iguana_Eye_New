#include "IEECSInputSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSInputSystem::IEECSInputSystem() :
    IEECSSystem(),
    data()
{
    IEECSInputSystem::attach(IEEntity(-1));
}

IEECSInputSystem::~IEECSInputSystem()
{

}

int IEECSInputSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = (int)entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.hasInput.append(true);

    return index;
}

bool IEECSInputSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.hasInput[indexToRemove] = data.hasInput[lastIndex];

    data.entity.removeLast();
    data.hasInput.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSInputSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

bool IEECSInputSystem::getHasInput(const int index) const
{
    if(!indexBoundCheck(index))
        return data.hasInput[0];

    return data.hasInput[index];
}

void IEECSInputSystem::setHasInput(const int index, const bool val)
{
    if(!indexBoundCheck(index))
        return;

    data.hasInput[index] = val;
}

QDataStream& IEECSInputSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSInputSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSInputSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSInputSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
