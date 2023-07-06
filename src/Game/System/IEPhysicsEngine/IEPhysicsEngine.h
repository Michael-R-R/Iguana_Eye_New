#pragma once

#include "IESystem.h"
#include "IESimulationCallback.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class IEPhysicsEngine : public IESystem
{
    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;
    physx::PxDefaultCpuDispatcher* pxCpuDispatcher;
    physx::PxTolerancesScale pxToleranceScale;
    physx::PxFoundation* pxFoundation;
    physx::PxPhysics* pxPhysics;
    physx::PxScene* pxScene;
    physx::PxMaterial* pxMaterial;

    IESimulationCallback simulationCallback;

    float worldGravity;
    float accumulator;
    float stepSize;

public:
    IEPhysicsEngine(QObject* parent = nullptr);
    ~IEPhysicsEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    void onUpdateFrame(const float dt);

    void addActorToScene(physx::PxActor* actor);
    void removeActorFromScene(physx::PxActor* actor);
    void releaseActor(physx::PxActor* actor);

    physx::PxDefaultCpuDispatcher& getCpuDispatcher() const { return *pxCpuDispatcher; }
    physx::PxPhysics& getPxPhysics() const { return *pxPhysics; }
    physx::PxMaterial& getPxMaterial() const { return *pxMaterial; }
    const IESimulationCallback& getSimulationCallback() const { return simulationCallback; }

private:
    physx::PxSceneDesc createSceneDesc();
};

