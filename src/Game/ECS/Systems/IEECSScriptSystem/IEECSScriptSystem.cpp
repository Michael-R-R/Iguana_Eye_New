#include "IEECSScriptSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSScriptSystem::IEECSScriptSystem() :
    IEECSSystem(),
    data()
{

}

void IEECSScriptSystem::startup(const GameStartEvent& event)
{

}

int IEECSScriptSystem::attach(const IEEntity entity)
{
    return -1;
}

bool IEECSScriptSystem::detach(const IEEntity entity)
{
    return false;
}

void IEECSScriptSystem::onUpdateFrame(ECSOnUpdateEvent*)
{

}
