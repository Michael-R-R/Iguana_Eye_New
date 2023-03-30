#include "IEECSCameraSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"
#include "IECameraManager.h"
#include "IEScriptEngine.h"
#include "IEECSTransformSystem.h"

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
    cameraManager = &event.getScene().getCameraManager();

    auto& scriptEngine = event.getScriptEngine();
    initalizeAllScripts(scriptEngine.getLua());
}

int IEECSCameraSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.cameraId.append(0);
    data.cameraScript.append(IECameraScript{});

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
    data.cameraScript[indexToRemove] = data.cameraScript[lastIndex];

    data.entity.removeLast();
    data.cameraId.removeLast();
    data.cameraScript.removeLast();

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

    data.cameraScript[activeIndex].update();

    auto transformSystem = event->getTransform();
    int transformIndex = transformSystem->lookUpIndex(activeEntity);
    auto& pos = transformSystem->getPosition(transformIndex);
    auto& rot = transformSystem->getRotation(transformIndex);

    IECamera* activeCamera = cameraManager->value(activeId);
    activeCamera->updateView(pos, rot.toVector3D());
}

void IEECSCameraSystem::initalizeAllScripts(sol::state& lua)
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.cameraScript[i].initalize(lua);
    }
}

void IEECSCameraSystem::startAllScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.cameraScript[i].start(data.entity[i]);
    }
}

bool IEECSCameraSystem::initalizeScript(const int index, sol::state& lua)
{
    if(!indexBoundCheck(index))
        return false;

    return data.cameraScript[index].initalize(lua);
}

void IEECSCameraSystem::startScript(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraScript[index].start(data.entity[index]);
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
    if(!indexBoundCheck(activeIndex))
        return nullptr;

    return cameraManager->value(data.cameraId[activeIndex]);
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
}

unsigned long long IEECSCameraSystem::getCameraId(const int index) const
{
    if(!indexBoundCheck(index))
        return 0;

    return data.cameraId[index];
}

IECameraScript* IEECSCameraSystem::getScript(const int index)
{
    if(!indexBoundCheck(index))
        return nullptr;

    return &data.cameraScript[index];
}

void IEECSCameraSystem::setCameraId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraId[index] = val;
}

void IEECSCameraSystem::setScript(const int index, const IECameraScript& val)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraScript[index] = val;
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
