#pragma once

#include <memory>

#include "IEObject.h"
#include "IESimulationCallback.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class GameStartEvent;

class IEPhysicsEngine : public IEObject
{
    Q_OBJECT

    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* pxCpuDispatcher;
    physx::PxTolerancesScale pxToleranceScale;
    physx::PxFoundation* pxFoundation;
    physx::PxPhysics* pxPhysics;
    physx::PxScene* pxScene;
    physx::PxMaterial* pxDefaultMaterial;

    std::unique_ptr<IESimulationCallback> simulationCallback;

    float worldGravity;

    float accumulator;
    float stepSize;

public:
    IEPhysicsEngine();
    ~IEPhysicsEngine();

    void startup(const GameStartEvent& event);
    void shutdown();
    void onUpdateFrame(const float dt);

    void addActorToScene(physx::PxActor* actor);
    void removeActorFromScene(physx::PxActor* actor);
    void releaseActor(physx::PxActor* actor);

    physx::PxPhysics* getPxPhysics() { return pxPhysics; }
    physx::PxMaterial* getDefaultPxMaterial() { return pxDefaultMaterial; }
    IESimulationCallback* getSimulationCallback() { return &(*simulationCallback); }
};

