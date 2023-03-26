#include "IEECSRigidbody3DSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEPhysicsEngine.h"
#include "IEECSTransformSystem.h"

IEECSRigidbody3DSystem::IEECSRigidbody3DSystem() :
    data(),
    awakeBodies(), sleepingBodies(),
    physicsEngine(nullptr)
{
    IEECSRigidbody3DSystem::attach(IEEntity(-1));
}

IEECSRigidbody3DSystem::~IEECSRigidbody3DSystem()
{
    physicsEngine = nullptr;
}

void IEECSRigidbody3DSystem::startup(const GameStartEvent& event)
{
    physicsEngine = &event.getPhysicsEngine();
}

int IEECSRigidbody3DSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.push_back(entity);
    data.rigidbody.push_back(IERigidBody());

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
    data.rigidbody[indexToRemove] = data.rigidbody[lastIndex];

    data.entity.removeLast();
    data.rigidbody.removeLast();

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
        IERigidBody& rigidbody = data.rigidbody[i];

        physx::PxTransform pxTransform = rigidbody.getActor()->getGlobalPose();
        physx::PxVec3 pxPos = pxTransform.p;
        physx::PxQuat pxQuat = pxTransform.q;

        float angle = 0.0f;
        physx::PxVec3 pxRot;
        pxQuat.toRadiansAndUnitAxis(angle, pxRot);

        const int transformIndex = transformSystem->lookUpIndex(data.entity[i]);
        transformSystem->setPosition(transformIndex, QVector3D(pxPos.x, pxPos.y, pxPos.z));
        transformSystem->setRotation(transformIndex, QVector4D(pxRot.x, pxRot.y, pxRot.z, qRadiansToDegrees(angle)));

        // TODO test
        qDebug() << pxPos.x << pxPos.y << pxPos.z;
    }
}

void IEECSRigidbody3DSystem::wakeup(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.rigidbody[index].wakeup(physicsEngine))
        return;

    sleepingBodies.remove(index);
    awakeBodies.insert(index);
}

void IEECSRigidbody3DSystem::putToSleep(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.rigidbody[index].putToSleep(physicsEngine))
        return;

    awakeBodies.remove(index);
    sleepingBodies.insert(index);
}

void IEECSRigidbody3DSystem::release(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.rigidbody[index].release(physicsEngine);

    awakeBodies.remove(index);
    sleepingBodies.remove(index);
}

const IERigidBody& IEECSRigidbody3DSystem::getRigidbody(const int index) const
{
    if(!indexBoundCheck(index))
        return data.rigidbody[0];

    return data.rigidbody[index];
}

void IEECSRigidbody3DSystem::setRigidbody(const int index, const IERigidBody& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rigidbody[index] = val;
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
