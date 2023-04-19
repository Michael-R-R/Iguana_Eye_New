#include "IEECSCameraSystem.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScriptEngine.h"
#include "IEScene.h"
#include "IECameraManager.h"
#include "IECamera.h"
#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSCameraSystem::IEECSCameraSystem(QObject* parent) :
    IEECSSystem(parent),
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
    data.cameraId.append(0);
    data.cameraScript.append(new IECameraScript(&data));

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
    data.cameraScript[indexToRemove] = data.cameraScript[lastIndex];

    data.entity.removeLast();
    data.cameraScript.removeLast();
    data.cameraId.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSCameraSystem::onUpdateFrame(ECSOnUpdateEvent& event)
{
    if(!indexBoundCheck(activeIndex))
        return;

    auto& activeEntity = data.entity[activeIndex];
    auto& activeId = data.cameraId[activeIndex];

    data.cameraScript[activeIndex]->update();

    auto& transformSystem = event.getTransform();
    int transformIndex = transformSystem.lookUpIndex(activeEntity);
    auto& pos = transformSystem.getPosition(transformIndex);
    auto& rot = transformSystem.getRotation(transformIndex);

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* cameraManager = scene->getCameraManager();

    auto* activeCamera = cameraManager->value<IECamera>(activeId);
    activeCamera->updateView(pos, rot.toVector3D());
}

void IEECSCameraSystem::initalize()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scriptEngine = game->getScriptEngine();
    auto& lua = scriptEngine->getLua();

    for(int i = 1; i < entityMap.size(); i++)
    {
        data.cameraScript[i]->initalize(lua);
        data.cameraScript[i]->start(data.entity[i]);
    }
}

void IEECSCameraSystem::removeScript(const int index)
{
    if(!indexBoundCheck(index))
        return;

    delete data.cameraScript[index];
    data.cameraScript[index] = new IECameraScript(&data);
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

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* cameraManager = scene->getCameraManager();

    return cameraManager->value<IECamera>(data.cameraId[activeIndex]);
}

IECamera* IEECSCameraSystem::getAttachedCamera(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* cameraManager = scene->getCameraManager();

    return cameraManager->value<IECamera>(data.cameraId[index]);
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

    return data.cameraScript[index];
}

void IEECSCameraSystem::setCameraId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.cameraId[index] = val;
}

void IEECSCameraSystem::setScript(const int index, IECameraScript* val)
{
    if(!indexBoundCheck(index))
        return;

    delete data.cameraScript[index];
    data.cameraScript[index] = val;
    val->setParent(&data);
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
