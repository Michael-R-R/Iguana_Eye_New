#include "IEECSMeshSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSMeshSystem::IEECSMeshSystem() :
    IEECSSystem(),
    data()
{

}

IEECSMeshSystem::~IEECSMeshSystem()
{

}

int IEECSMeshSystem::attach(const IEEntity entity)
{
    return -1;
}

bool IEECSMeshSystem::detach(const IEEntity entity)
{
    return false;
}

void IEECSMeshSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

void IEECSMeshSystem::onPostUpdateFrame()
{
    // Not used
}

void IEECSMeshSystem::onRenderFrame()
{
    // Not used
}
