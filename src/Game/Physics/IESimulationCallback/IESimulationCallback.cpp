#include "IESimulationCallback.h"
#include <QDebug>

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
        qDebug() << "Wake:" << (int)(size_t)actors[count]->userData;
    }
}

void IESimulationCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        qDebug() << "Sleep:" << (int)(size_t)actors[count]->userData;
    }
}

void IESimulationCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
    while(count--)
    {
        const physx::PxTriggerPair& current = *pairs++;
        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            qDebug() << "On Trigger Enter(trigger actor):" << (int)(size_t)current.triggerActor->userData;
            qDebug() << "On Trigger Enter(other actor):" << (int)(size_t)current.otherActor->userData;
        }
        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            qDebug() << "On Trigger Exit(trigger actor):" << (int)(size_t)current.triggerActor->userData;
            qDebug() << "On Trigger Exit(other actor):" << (int)(size_t)current.otherActor->userData;
        }
    }
}
