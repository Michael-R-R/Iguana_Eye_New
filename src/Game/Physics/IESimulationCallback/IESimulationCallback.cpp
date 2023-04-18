#include "IESimulationCallback.h"
#include "IEEntity.h"

IESimulationCallback::IESimulationCallback()
{

}

IESimulationCallback::~IESimulationCallback()
{

}

void IESimulationCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        auto* actor = actors[count];
        const IEEntity entity = IEEntity((int)(size_t)actor->userData);

        emit onWakeRigidbody(entity);
    }
}

void IESimulationCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        auto* actor = actors[count];
        const IEEntity entity = IEEntity((int)(size_t)actor->userData);

        emit onSleepRigidbody(entity);
    }
}

void IESimulationCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
    while(count--)
    {
        const physx::PxTriggerPair& current = *pairs++;

        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            const IEEntity triggerEntity = IEEntity((int)(size_t)current.triggerActor->userData);
            const IEEntity otherEntity = IEEntity((int)(size_t)current.otherActor->userData);

            emit onTriggerEnter(triggerEntity, otherEntity);
        }

        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            const IEEntity triggerEntity = IEEntity((int)(size_t)current.triggerActor->userData);
            const IEEntity otherEntity = IEEntity((int)(size_t)current.otherActor->userData);

            emit onTriggerLeave(triggerEntity, otherEntity);
        }
    }
}
