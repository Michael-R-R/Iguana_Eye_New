#pragma once

#include "physx/PxPhysics.h"
#include "physx/PxPhysicsAPI.h"
#include "physx/PxRigidDynamic.h"
#include "physx/geometry/PxGeometry.h"
#include "physx/geometry/PxBoxGeometry.h"
#include "physx/foundation/PxTransform.h"
#include "physx/foundation/PxVec3.h"
#include "physx/extensions/PxDefaultAllocator.h"
#include "physx/extensions/PxDefaultErrorCallback.h"
#include "physx/extensions/PxDefaultCpuDispatcher.h"
#include "physx/extensions/PxDefaultSimulationFilterShader.h"

#include "IEEntity.h"
#include <QVector>
#include <QVector4D>
#include <QMatrix4x4>

class GameStartEvent;
class IEGame;
class IEInput;
class IECameraManager;
class IEECSCameraSystem;
class IEECSTransformSystem;

class IETBasicPhysics
{
    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* defaultDispatcher;
    physx::PxTolerancesScale toleranceScale;
    physx::PxFoundation* foundation;
    physx::PxPhysics* physics;
    physx::PxScene* scene;
    physx::PxMaterial* material;

    QVector<physx::PxRigidDynamic*> dynamicItems;
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

    physx::PxRigidStatic* createStatic(const physx::PxTransform& transform,
                                       const physx::PxGeometry& geometry);

    physx::PxRigidDynamic* createDynamic(const physx::PxTransform& transform,
                                         const physx::PxGeometry& geometry);

private:
    void createGround();
    void createRenderable(const GameStartEvent& event);
    void createEntities(const GameStartEvent& event, const unsigned long long rendId);
    void updateEntities();
    QVector3D scrPosToWorldRay();
};

