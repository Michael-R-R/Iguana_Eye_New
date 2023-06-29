#include "IEECSCameraSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IECamera.h"
#include "IECameraManager.h"
#include "IEScriptEngine.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"

IEECSCameraSystem::IEECSCameraSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSCameraSystem).hash_code(), parent),
    data(), activeIndex(-1),
    cameraManager(nullptr),
    sEngine(nullptr),
    tSystem(nullptr)
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
    data.cameraId.append(0);
    data.script.append(new IEScript(&data));

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

    this->removeScript(indexToRemove);

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.cameraId[indexToRemove] = data.cameraId[lastIndex];
    data.script[indexToRemove] = data.script[lastIndex];

    data.entity.removeLast();
    data.script.removeLast();
    data.cameraId.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSCameraSystem::startUp(const IEGame& game)
{
    cameraManager = game.getSystem<IEScene>()->getCameraManager();
    sEngine = game.getSystem<IEScriptEngine>();
    tSystem = game.getSystem<IEECS>()->getComponent<IEECSTransformSystem>();
}

void IEECSCameraSystem::shutdown(const IEGame&)
{
    removeAll();

    cameraManager = nullptr;
    sEngine = nullptr;
    tSystem = nullptr;
}

void IEECSCameraSystem::onDeserialize(const IEGame&)
{
    removeAll();
}

void IEECSCameraSystem::onUpdateFrame()
{
    if(!indexBoundCheck(activeIndex))
        return;

    auto& activeEntity = data.entity[activeIndex];
    auto& activeId = data.cameraId[activeIndex];

    data.script[activeIndex]->update();

    int transformIndex = tSystem->lookUpIndex(activeEntity);
    auto& pos = tSystem->getPosition(transformIndex);
    auto& rot = tSystem->getRotation(transformIndex);

    auto* activeCamera = cameraManager->value<IECamera>(activeId);
    activeCamera->updateView(pos, rot.toVector3D());
}

void IEECSCameraSystem::initAll()
{
    for (int i = 1; i < entityMap.size(); i++)
    {
        data.script[i]->init(sEngine->getLua(), data.entity[i]);
    }
}

void IEECSCameraSystem::startAll()
{
    for (int i = 1; i < entityMap.size(); i++)
    {
        data.script[i]->start();
    }
}

void IEECSCameraSystem::init(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.script[index]->init(sEngine->getLua(), data.entity[index]);
}

void IEECSCameraSystem::start(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.script[index]->start();
}

void IEECSCameraSystem::removeScript(const int index)
{
    if(!indexBoundCheck(index))
        return;

    delete data.script[index];
    data.script[index] = nullptr;
}

void IEECSCameraSystem::removeAll()
{
    foreach(auto* i, data.script)
    {
        delete i;
        i = nullptr;
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

    return cameraManager->value<IECamera>(data.cameraId[activeIndex]);
}

IECamera* IEECSCameraSystem::getAttachedCamera(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return cameraManager->value<IECamera>(data.cameraId[index]);
}

void IEECSCameraSystem::setActiveIndex(const int val)
{
    activeIndex = val;
}

uint64_t IEECSCameraSystem::getCameraId(const int index) const
{
    if(!indexBoundCheck(index))
        return 0;

    return data.cameraId[index];
}

const IEScript* IEECSCameraSystem::getScript(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return data.script[index];
}

void IEECSCameraSystem::setScript(const int index, IEScript* val)
{
    if(!indexBoundCheck(index))
        return;

    delete data.script[index];
    data.script[index] = val;
    val->setParent(&data);
}

void IEECSCameraSystem::setCameraId(const int index, const uint64_t val)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraId[index] = val;
}

void IEECSCameraSystem::cacheScripts()
{
    foreach (auto* i, data.script)
    {
        i->dataFrom();
    }
}

void IEECSCameraSystem::decacheScripts()
{
    foreach (auto* i, data.script)
    {
        i->dataTo();
    }
}

QDataStream& IEECSCameraSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSCameraSystem&>(obj);

    out << system.entityMap << system.data << system.activeIndex;

    const_cast<IEECSCameraSystem&>(system).cacheScripts();

    return out;
}

QDataStream& IEECSCameraSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSCameraSystem&>(obj);

    in >> system.entityMap >> system.data >> system.activeIndex;

    system.initAll();
    system.decacheScripts();

    return in;
}
