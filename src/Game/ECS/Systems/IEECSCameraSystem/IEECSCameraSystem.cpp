#include "IEECSCameraSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"
#include "IECameraManager.h"
#include "IEECSTransformSystem.h"

IEECSCameraSystem::IEECSCameraSystem() :
    data(),
    activeIndex(-1),
    hasDirtyProjection(true),
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
    cameraManager = &event.getScene().getCameraManager();
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

    IECamera* activeCamera = cameraManager->value(activeId);
    activeCamera->updateView(pos, rot.toVector3D());
}

int IEECSCameraSystem::getActiveIndex() const
{
    return activeIndex;
}

bool IEECSCameraSystem::getHasDirtyProj() const
{
    return hasDirtyProjection;
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

    return cameraManager->value(id);
}

IECamera* IEECSCameraSystem::getAttachedCamera(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return cameraManager->value(data.cameraId[index]);
}

void IEECSCameraSystem::setActiveIndex(const int val)
{
    activeIndex = val;
    hasDirtyProjection = true;
}

void IEECSCameraSystem::setHasDirtyProj(const bool val)
{
    hasDirtyProjection = val;
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

QDataStream& IEECSCameraSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSCameraSystem&>(obj);

    out << system.entityMap << system.data << system.activeIndex;

    return out;
}

QDataStream& IEECSCameraSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSCameraSystem&>(obj);

    in >> system.entityMap >> system.data >> system.activeIndex;

    return in;
}
