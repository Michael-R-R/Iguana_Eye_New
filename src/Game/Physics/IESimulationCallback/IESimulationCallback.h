#pragma once

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class GameStartEvent;
class IEECSScriptSystem;

class IESimulationCallback : public physx::PxSimulationEventCallback
{
    // DOES NOT OWN THESE POINTERS
    IEECSScriptSystem* scriptSystem;

public:
    IESimulationCallback(const GameStartEvent& event);
    ~IESimulationCallback();

    void onWake(physx::PxActor** actors, physx::PxU32 count) override;
    void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
    void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
    void onConstraintBreak(physx::PxConstraintInfo*, physx::PxU32) override {}
    void onContact(const physx::PxContactPairHeader&, const physx::PxContactPair*, physx::PxU32) override {}
    void onAdvance(const physx::PxRigidBody* const* , const physx::PxTransform*, const physx::PxU32) override {}
};

