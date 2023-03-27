#pragma once

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

#include "IEEntity.h"
#include "IERigidBody.h"
#include "IEBoxCollider.h"
#include <QVector>
#include <QVector4D>
#include <QMatrix4x4>
#include <vector>

class GameStartEvent;
class IEGame;
class IEInput;
class IECameraManager;
class IEECSCameraSystem;
class IEECSTransformSystem;

class ContactReportCallback : public physx::PxSimulationEventCallback
{

public:
    ContactReportCallback() {}
    ~ContactReportCallback() {}

    void onConstraintBreak(physx::PxConstraintInfo*, physx::PxU32) override {}
    void onWake(physx::PxActor** actors, physx::PxU32 count) override;
    void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
    void onContact(const physx::PxContactPairHeader&, const physx::PxContactPair*, physx::PxU32) override {}
    void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
    void onAdvance(const physx::PxRigidBody* const* , const physx::PxTransform*, const physx::PxU32) override {}
};

class IETBasicPhysics
{
    ContactReportCallback reportCallback;

    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* defaultDispatcher;
    physx::PxTolerancesScale toleranceScale;
    physx::PxFoundation* pxFoundation;
    physx::PxPhysics* pxPhysics;
    physx::PxScene* pxScene;
    physx::PxMaterial* pxMaterial;

    float accumulator = 0.0f;
    float stepSize = 1.0f / 60.f;

    std::vector<std::unique_ptr<IERigidBody>> dynamicBodies;
    std::vector<std::unique_ptr<IEBoxCollider>> boxColliders;
    QVector<IEEntity> entities;
    IEGame* game = nullptr;
    IEInput* input = nullptr;
    IECameraManager* cameraManager = nullptr;
    IEECSTransformSystem* transformSystem = nullptr;

public:
    IETBasicPhysics();
    ~IETBasicPhysics();

    void startup(const GameStartEvent& event);
    void shutdown();
    void simulate(const float dt);

private:
    void createGround();
    void createRenderable(const GameStartEvent& event);
    void createEntities(const GameStartEvent& event, const unsigned long long rendId);
    void updateEntities();
    QVector3D scrPosToWorldRay();
    void castRay();
};
