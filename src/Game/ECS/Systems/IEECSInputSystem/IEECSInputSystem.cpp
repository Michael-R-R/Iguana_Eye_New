#include "IEECSInputSystem.h"

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

    data.entityList.append(entity);
    data.hasInputList.append(true);

    return index;
}

bool IEECSInputSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];
    int lastIndex = entityMap.size() - 1;

    IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.hasInputList[indexToRemove] = data.hasInputList[lastIndex];

    data.entityList.removeAt(lastIndex);
    data.hasInputList.removeAt(lastIndex);

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSInputSystem::onUpdateFrame()
{
    // Not used
}

void IEECSInputSystem::onPostUpdateFrame()
{
    // Not used
}

void IEECSInputSystem::onRenderFrame()
{
    // Not used
}

bool IEECSInputSystem::getHasInput(const int index) const
{
    if(!indexBoundCheck(index))
        return data.hasInputList[0];

    return data.hasInputList[index];
}

void IEECSInputSystem::setHasInput(const int index, const bool val)
{
    if(!indexBoundCheck(index))
        return;

    data.hasInputList[index] = val;
}
