#include "IEECSCameraSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSCameraSystem::IEECSCameraSystem() :
    data()
{

}

IEECSCameraSystem::~IEECSCameraSystem()
{

}

void IEECSCameraSystem::startup(const GameStartEvent&)
{

}

int IEECSCameraSystem::attach(const IEEntity entity)
{
    return -1;
}

bool IEECSCameraSystem::detach(const IEEntity entity)
{
    return false;
}

void IEECSCameraSystem::onUpdateFrame(ECSOnUpdateEvent*)
{

}
