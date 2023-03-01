#include "IEECSInputSystem.h"
#include "GameStartEvent.h"
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

void IEECSInputSystem::startup(const GameStartEvent&)
{
    // Not used
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
