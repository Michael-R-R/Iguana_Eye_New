#pragma once

#include <QMap>

#include "IEObject.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "IEEntity.h"

class IEGame;
class IEInput;
class ECamera;
class IEBoxRigidbody;

class EPhysicsEngine: public IEObject
{
    Q_OBJECT

    physx::PxScene* pxScene;
    physx::PxReal raycastDistance;
    physx::PxQueryFilterData filterFlag;

    QMap<IEEntity, IEBoxRigidbody*> rigidbodies;

    bool isButtonHeld;

public:
    EPhysicsEngine(QObject* parent = nullptr);
    ~EPhysicsEngine();

    void startup(IEGame& game);
    void shutdown();
    void onUpdateFrame(IEInput& input, ECamera& camera);

private:
    void onInitRigidbodies(IEGame& game);
    std::tuple<bool, physx::PxRaycastBuffer> castRay(const IEInput& input,
                                                     const ECamera& camera);

signals:
    void entitySelected(const IEEntity& entity);
    void selectionCleared();
};

