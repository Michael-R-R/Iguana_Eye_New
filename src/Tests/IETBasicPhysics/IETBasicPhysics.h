#pragma once

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

#include "IEEntity.h"
#include "IERigidBody.h"
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

class IETBasicPhysics
{
    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* defaultDispatcher;
    physx::PxTolerancesScale toleranceScale;
    physx::PxFoundation* pxFoundation;
    physx::PxPhysics* pxPhysics;
    physx::PxScene* pxScene;
    physx::PxMaterial* pxMaterial;

    std::vector<std::unique_ptr<IERigidBody>> rigidBodies;
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

