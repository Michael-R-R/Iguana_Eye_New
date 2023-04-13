#pragma once

#include <QSharedPointer>
#include <QMap>

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "IEEntity.h"

class IEGame;
class IEBoxRigidbody;

class EPhysicsEngine
{
    physx::PxScene* pxScene;
    physx::PxMaterial* pxMaterial;

    QMap<IEEntity, QSharedPointer<IEBoxRigidbody>> rigidbodies;

public:
    EPhysicsEngine(IEGame& game);
    ~EPhysicsEngine();

    void onUpdateFrame();

private:
    void setup(IEGame& game);
    void createRigidbodies();
};

