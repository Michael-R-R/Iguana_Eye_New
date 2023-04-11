#pragma once

#include <QSharedPointer>

#include "IEGameSystem.h"
#include "IESimulationCallback.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class GameStartEvent;

class IEPhysicsEngine : public IEGameSystem
{
    IEPhysicsEngine();
    static IEPhysicsEngine mInstance;

    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* pxCpuDispatcher;
    physx::PxTolerancesScale pxToleranceScale;
    physx::PxFoundation* pxFoundation;
    physx::PxPhysics* pxPhysics;
    physx::PxScene* pxScene;
    physx::PxMaterial* pxMaterial;

    QSharedPointer<IESimulationCallback> simulationCallback;

    float worldGravity;

    float accumulator;
    float stepSize;

public:
    static IEPhysicsEngine& instance();
    ~IEPhysicsEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    void onUpdateFrame(const float dt);

    void addActorToScene(physx::PxActor* actor);
    void removeActorFromScene(physx::PxActor* actor);
    void releaseActor(physx::PxActor* actor);

    physx::PxPhysics* getPxPhysics() const { return pxPhysics; }
    physx::PxMaterial* getPxMaterial() const { return pxMaterial; }
    QSharedPointer<IESimulationCallback> getSimulationCallback() const { return simulationCallback; }
};

