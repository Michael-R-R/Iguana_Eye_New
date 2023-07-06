#pragma once

#include "IEObject.h"
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

class IEEntity;

class IESimulationCallback : public IEObject, public physx::PxSimulationEventCallback
{
    Q_OBJECT

public:
    IESimulationCallback();
    ~IESimulationCallback();

    void onWake(physx::PxActor** actors, physx::PxU32 count) override;
    void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
    void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
    void onConstraintBreak(physx::PxConstraintInfo*, physx::PxU32) override {}
    void onContact(const physx::PxContactPairHeader&, const physx::PxContactPair*, physx::PxU32) override {}
    void onAdvance(const physx::PxRigidBody* const* , const physx::PxTransform*, const physx::PxU32) override {}

signals:
    void onWakeRigidbody(const IEEntity& entity);
    void onSleepRigidbody(const IEEntity& entity);
    void onTriggerEnter(const IEEntity& triggerEntity, const IEEntity& otherEntity);
    void onTriggerLeave(const IEEntity& triggerEntity, const IEEntity& otherEntity);
};

