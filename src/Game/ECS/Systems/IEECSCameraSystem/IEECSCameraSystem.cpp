#include "IEECSCameraSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"

IEECSCameraSystem::IEECSCameraSystem() :
    data(),
    activeIndex(-1),
    cameraManager(nullptr)
{
    IEECSCameraSystem::attach(IEEntity(-1));
}

IEECSCameraSystem::~IEECSCameraSystem()
{
    cameraManager = nullptr;
}

void IEECSCameraSystem::startup(const GameStartEvent& event)
{
    cameraManager = event.getScene()->getCameraManager();
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

    if(indexToRemove == activeIndex)
        activeIndex = -1;

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

void IEECSCameraSystem::onUpdateFrame(ECSOnUpdateEvent* event)
{
    if(!indexBoundCheck(activeIndex))
        return;

    auto& activeEntity = data.entity[activeIndex];
    auto& activeId = data.cameraId[activeIndex];

    auto transformSystem = event->getTransform();
    int transformIndex = transformSystem->lookUpIndex(activeEntity);
    auto& pos = transformSystem->getPosition(transformIndex);
    auto& rot = transformSystem->getRotation(transformIndex);

    IECamera* activeCamera = cameraManager->getValue(activeId);
    activeCamera->updateView(pos, rot);
}

int IEECSCameraSystem::getActiveIndex() const
{
    return activeIndex;
}

IEEntity IEECSCameraSystem::getActiveEntity() const
{
    if(!indexBoundCheck(activeIndex))
        return IEEntity(-1);

    return data.entity[activeIndex];
}

IECamera* IEECSCameraSystem::getActiveCamera() const
{
    auto id = (indexBoundCheck(activeIndex)) ? data.cameraId[activeIndex] : cameraManager->getDefaultResourceId();

    return cameraManager->getValue(id);
}

IECamera* IEECSCameraSystem::getAttachedCamera(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return cameraManager->getValue(data.cameraId[index]);
}

void IEECSCameraSystem::setActiveIndex(const int val)
{
    activeIndex = val;
}

unsigned long long IEECSCameraSystem::getCameraId(const int index) const
{
    if(!indexBoundCheck(index))
        return 0;

    return data.cameraId[index];
}

void IEECSCameraSystem::setCameraId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraId[index] = val;
}
