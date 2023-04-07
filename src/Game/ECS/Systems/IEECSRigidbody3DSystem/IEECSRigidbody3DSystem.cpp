#include "IEECSRigidbody3DSystem.h"
#include "IEGame.h"
#include "IESimulationCallback.h"
#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSRigidbody3DSystem::IEECSRigidbody3DSystem() :
    data(),
    awakeBodies(),
    sleepingBodies()
{
    IEECSRigidbody3DSystem::attach(IEEntity(-1));

    auto& engine = IEPhysicsEngine::instance();
    auto* simCallback = engine.getSimulationCallback();
    connect(simCallback, &IESimulationCallback::onWakeRigidbody, this, &IEECSRigidbody3DSystem::activateRigidbody);
    connect(simCallback, &IESimulationCallback::onSleepRigidbody, this, &IEECSRigidbody3DSystem::deactivateRigidbody);
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
    data.rigidbody.push_back(nullptr);

    return index;
}

bool IEECSRigidbody3DSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    this->release(indexToRemove);

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.rigidbody[indexToRemove] = std::move(data.rigidbody[lastIndex]);

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

void IEECSRigidbody3DSystem::onUpdateFrame(ECSOnUpdateEvent* event)
{
    auto* transformSystem = event->getTransform();

    for(const auto& i : awakeBodies)
    {
        if(!data.rigidbody[i])
            continue;

        IERigidBody& rigidbody = *data.rigidbody[i];

        physx::PxVec3 pxPos = rigidbody.getGlobalPos();
        physx::PxQuat pxQuat = rigidbody.getGlobalQuat();

        float angle = 0.0f;
        physx::PxVec3 pxRot;
        pxQuat.toRadiansAndUnitAxis(angle, pxRot);

        const int transformIndex = transformSystem->lookUpIndex(data.entity[i]);
        transformSystem->setPosition(transformIndex, QVector3D(pxPos.x, pxPos.y, pxPos.z));
        transformSystem->setRotation(transformIndex, QVector4D(pxRot.x, pxRot.y, pxRot.z, qRadiansToDegrees(angle)));

        qDebug() << pxPos.x << pxPos.y << pxPos.z;
    }
}

void IEECSRigidbody3DSystem::play(IEGame&)
{
    auto& engine = IEPhysicsEngine::instance();

    for(int i = 1; i < data.rigidbody.size(); i++)
    {
        awakeBodies.insert(i);
        engine.addActorToScene(data.rigidbody[i]->getActor());
    }
}

void IEECSRigidbody3DSystem::stop(IEGame&)
{
    sleepingBodies.clear();
    awakeBodies.clear();
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

void IEECSRigidbody3DSystem::putToSleep(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.rigidbody[index]->putToSleep())
        return;

    awakeBodies.remove(index);
    sleepingBodies.insert(index);
}

void IEECSRigidbody3DSystem::release(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.rigidbody[index]->release();

    awakeBodies.remove(index);
    sleepingBodies.remove(index);
}

IERigidBody* IEECSRigidbody3DSystem::getRigidbody(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return &(*data.rigidbody[index]);
}

void IEECSRigidbody3DSystem::setRigidbody(const int index, std::unique_ptr<IERigidBody> val)
{
    if(!indexBoundCheck(index))
        return;

    data.rigidbody[index] = std::move(val);
}

void IEECSRigidbody3DSystem::activateRigidbody(const IEEntity& entity)
{
    const int index = this->lookUpIndex(entity);
    if(!indexBoundCheck(index))
        return;

    sleepingBodies.remove(index);
    awakeBodies.insert(index);
}

void IEECSRigidbody3DSystem::deactivateRigidbody(const IEEntity& entity)
{
    const int index = this->lookUpIndex(entity);
    if(!indexBoundCheck(index))
        return;

    awakeBodies.remove(index);
    sleepingBodies.insert(index);
}

QDataStream& IEECSRigidbody3DSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSRigidbody3DSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSRigidbody3DSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSRigidbody3DSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
