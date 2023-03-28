#include "IESimulationCallback.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSScriptSystem.h"
#include <QDebug>

IESimulationCallback::IESimulationCallback(const GameStartEvent& event)
{
    auto& ecs = event.getScene().getECS();
    scriptSystem = ecs.getComponent<IEECSScriptSystem>("Script");
}

IESimulationCallback::~IESimulationCallback()
{
    scriptSystem = nullptr;
}

void IESimulationCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        // TODO implement
        qDebug() << "Wake:" << (int)(size_t)actors[count]->userData;
    }
}

void IESimulationCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        // TODO implement
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
            const IEEntity triggerEntity = IEEntity((int)(size_t)current.triggerActor->userData);
            const IEEntity otherEntity = (int)(size_t)current.otherActor->userData;;

            const int triggerIndex = scriptSystem->lookUpIndex(triggerEntity);
            auto scriptCollection = scriptSystem->getScriptCollection(triggerIndex);
            for(const auto& i : scriptCollection)
            {
                sol::function func = i->getFunc("onTriggerEnter");
                func(otherEntity);
            }
        }

        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            const IEEntity triggerEntity = IEEntity((int)(size_t)current.triggerActor->userData);
            const IEEntity otherEntity = (int)(size_t)current.otherActor->userData;;

            const int triggerIndex = scriptSystem->lookUpIndex(triggerEntity);
            auto scriptCollection = scriptSystem->getScriptCollection(triggerIndex);
            for(const auto& i : scriptCollection)
            {
                sol::function func = i->getFunc("onTriggerLeave");
                func(otherEntity);
            }
        }
    }
}
