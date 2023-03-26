#pragma once

#include <memory>

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

#include "IESimulationCallback.h"

class GameStartEvent;

class IEPhysicsEngine
{
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
};

