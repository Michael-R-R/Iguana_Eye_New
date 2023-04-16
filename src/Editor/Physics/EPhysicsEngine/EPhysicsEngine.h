#pragma once

#include <QSharedPointer>
#include <QMap>

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "IEEntity.h"

class IEGame;
class IEInput;
class ECamera;
class IEBoxRigidbody;

class EPhysicsEngine
{
    physx::PxScene* pxScene;
    physx::PxReal raycastDistance;
    physx::PxQueryFilterData filterFlag;

    QMap<IEEntity, QSharedPointer<IEBoxRigidbody>> rigidbodies;

public:
    EPhysicsEngine();
    ~EPhysicsEngine();

    void startup(IEGame& game);
    void shutdown();
    void onUpdateFrame(IEInput& input, ECamera& camera);

private:
    void onInitRigidbodies(IEGame& game);
    void castRay(IEInput& input, ECamera& camera);
};

