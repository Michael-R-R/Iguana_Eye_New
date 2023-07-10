#include "IEECSRigidbody3DSystem.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "IESimulationCallback.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"

IEECSRigidbody3DSystem::IEECSRigidbody3DSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSRigidbody3DSystem).hash_code(), parent),
    data(),
    awakeBodies(), sleepingBodies(),
    pEngine(nullptr), tSystem(nullptr)
{
    IEECSRigidbody3DSystem::attach(IEEntity(-1));
}

IEECSRigidbody3DSystem::~IEECSRigidbody3DSystem()
{

}

int IEECSRigidbody3DSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.push_back(entity);
    data.rigidbody.push_back(new IEBaseRigidbody(&data));

    return index;
}

bool IEECSRigidbody3DSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    this->removeRigidbody(indexToRemove);

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.rigidbody[indexToRemove] = data.rigidbody[lastIndex];

    data.entity.removeLast();
    data.rigidbody.pop_back();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    // Update awake and sleeping indexes
    if(awakeBodies.contains(lastIndex))
    {
        awakeBodies.insert(indexToRemove);
        awakeBodies.remove(lastIndex);
    }
    if(sleepingBodies.contains(lastIndex))
    {
        sleepingBodies.insert(indexToRemove);
        sleepingBodies.remove(lastIndex);
    }

    return true;
}

void IEECSRigidbody3DSystem::startUp(const IEGame& game)
{
    pEngine = game.getSystem<IEPhysicsEngine>();
    auto& simCallback = pEngine->getSimulationCallback();
    connect(&simCallback, &IESimulationCallback::onWakeRigidbody, this, &IEECSRigidbody3DSystem::wakeRigidbody);
    connect(&simCallback, &IESimulationCallback::onSleepRigidbody, this, &IEECSRigidbody3DSystem::sleepRigidbody);

    tSystem = game.getSystem<IEECS>()->getComponent<IEECSTransformSystem>();
}

void IEECSRigidbody3DSystem::shutdown(const IEGame&)
{
    removeAll();

    auto& simCallback = pEngine->getSimulationCallback();
    disconnect(&simCallback, &IESimulationCallback::onWakeRigidbody, this, &IEECSRigidbody3DSystem::wakeRigidbody);
    disconnect(&simCallback, &IESimulationCallback::onSleepRigidbody, this, &IEECSRigidbody3DSystem::sleepRigidbody);

    pEngine = nullptr;
    tSystem = nullptr;
}

void IEECSRigidbody3DSystem::onDeserialize(const IEGame&)
{
    removeAll();
}

void IEECSRigidbody3DSystem::onUpdateFrame()
{
    for(const auto& i : awakeBodies)
    {
        if(!data.rigidbody[i])
            continue;

        IEBaseRigidbody& rigidbody = *data.rigidbody[i];

        physx::PxVec3 pxPos = rigidbody.getGlobalPos();
        physx::PxQuat pxQuat = rigidbody.getGlobalQuat();

        float angle = 0.0f;
        physx::PxVec3 pxRot;
        pxQuat.toRadiansAndUnitAxis(angle, pxRot);

        const int transformIndex = tSystem->lookUpIndex(data.entity[i]);
        tSystem->setPosition(transformIndex, glm::vec3(pxPos.x, pxPos.y, pxPos.z));
        tSystem->setRotation(transformIndex, glm::vec4(pxRot.x, pxRot.y, pxRot.z, glm::degrees(angle)));

        qDebug() << pxPos.x << pxPos.y << pxPos.z;
    }
}

void IEECSRigidbody3DSystem::wakeAll()
{
    for(int i = 1; i < data.rigidbody.size(); i++)
    {
        auto* rigidbody = data.rigidbody[i];
        if(!rigidbody)
            continue;

        if(!rigidbody->wakeup())
            return;

        sleepingBodies.remove(i);
        awakeBodies.insert(i);
    }
}

void IEECSRigidbody3DSystem::sleepAll()
{
    for(int i = 1; i < data.rigidbody.size(); i++)
    {
        auto* rigidbody = data.rigidbody[i];
        if(!rigidbody)
            continue;

        if(!rigidbody->sleep())
            return;

        sleepingBodies.insert(i);
        awakeBodies.remove(i);
    }
}

void IEECSRigidbody3DSystem::wakeup(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.rigidbody[index]->wakeup())
        return;

    sleepingBodies.remove(index);
    awakeBodies.insert(index);
}

void IEECSRigidbody3DSystem::sleep(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.rigidbody[index]->sleep())
        return;

    awakeBodies.remove(index);
    sleepingBodies.insert(index);
}

void IEECSRigidbody3DSystem::removeRigidbody(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.rigidbody[index]->release();
    delete data.rigidbody[index];
    data.rigidbody[index] = nullptr;

    awakeBodies.remove(index);
    sleepingBodies.remove(index);
}

void IEECSRigidbody3DSystem::removeAll()
{
    for (int i = 0; i < data.rigidbody.size(); i++)
    {
        data.rigidbody[i]->release();
        delete data.rigidbody[i];
        data.rigidbody[i] = nullptr;

        awakeBodies.remove(i);
        sleepingBodies.remove(i);
    }
}

IEBaseRigidbody* IEECSRigidbody3DSystem::getRigidbody(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return data.rigidbody[index];
}

void IEECSRigidbody3DSystem::setRigidbody(const int index, IEBaseRigidbody* val)
{
    if(!indexBoundCheck(index))
        return;

    delete data.rigidbody[index];
    data.rigidbody[index] = val;
    val->setParent(&data);
}

void IEECSRigidbody3DSystem::wakeRigidbody(const IEEntity& entity)
{
    const int index = this->lookUpIndex(entity);
    if(!indexBoundCheck(index))
        return;

    sleepingBodies.remove(index);
    awakeBodies.insert(index);
}

void IEECSRigidbody3DSystem::sleepRigidbody(const IEEntity& entity)
{
    const int index = this->lookUpIndex(entity);
    if(!indexBoundCheck(index))
        return;

    awakeBodies.remove(index);
    sleepingBodies.insert(index);
}

QDataStream& IEECSRigidbody3DSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& system = static_cast<const IEECSRigidbody3DSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSRigidbody3DSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& system = static_cast<IEECSRigidbody3DSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
