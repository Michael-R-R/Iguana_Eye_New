#include "IEECSCameraSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSCameraSystem::IEECSCameraSystem() :
    data()
{
    IEECSCameraSystem::attach(IEEntity(-1));
}

IEECSCameraSystem::~IEECSCameraSystem()
{

}

void IEECSCameraSystem::startup(const GameStartEvent&)
{

}

int IEECSCameraSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.cameraId.append(0);

    return index;
}

bool IEECSCameraSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.cameraId[indexToRemove] = data.cameraId[lastIndex];

    data.entity.removeLast();
    data.cameraId.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSCameraSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // TODO update view
}
