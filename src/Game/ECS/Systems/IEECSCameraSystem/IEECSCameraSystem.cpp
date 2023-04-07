#include "IEECSCameraSystem.h"
#include "IEGame.h"
#include "IEScriptEngine.h"
#include "IEScene.h"
#include "IECameraManager.h"
#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSCameraSystem::IEECSCameraSystem() :
    data(),
    activeIndex(-1)
{
    IEECSCameraSystem::attach(IEEntity(-1));
}

IEECSCameraSystem::~IEECSCameraSystem()
{

}

int IEECSCameraSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.cameraScript.append(IECameraScript{});
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
    data.cameraScript[indexToRemove] = data.cameraScript[lastIndex];
    data.cameraId[indexToRemove] = data.cameraId[lastIndex];

    data.entity.removeLast();
    data.cameraScript.removeLast();
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

    data.cameraScript[activeIndex].update();

    auto transformSystem = event->getTransform();
    int transformIndex = transformSystem->lookUpIndex(activeEntity);
    auto& pos = transformSystem->getPosition(transformIndex);
    auto& rot = transformSystem->getRotation(transformIndex);

    auto& cameraManager = IEScene::instance().getCameraManager();

    IECamera* activeCamera = cameraManager.value(activeId);
    activeCamera->updateView(pos, rot.toVector3D());
}

void IEECSCameraSystem::play(IEGame&)
{
    auto& scriptEngine = IEScriptEngine::instance();
    auto& lua = scriptEngine.getLua();

    for(int i = 1; i < entityMap.size(); i++)
    {
        data.cameraScript[i].initalize(lua);
        data.cameraScript[i].start(data.entity[i]);
    }
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

    auto& cameraManager = IEScene::instance().getCameraManager();

    return cameraManager.value(data.cameraId[activeIndex]);
}

IECamera* IEECSCameraSystem::getAttachedCamera(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    auto& cameraManager = IEScene::instance().getCameraManager();

    return cameraManager.value(data.cameraId[index]);
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

const IECameraScript* IEECSCameraSystem::getScript(const int index) const
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
