#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"
#include "IEECSHierarchySystem.h"

IEECSTransformSystem::IEECSTransformSystem() :
    IEECSSystem(),
    data()
{

}

IEECSTransformSystem::~IEECSTransformSystem()
{

}

int IEECSTransformSystem::attach(const IEEntity entity)
{
    return -1;
}

bool IEECSTransformSystem::detach(const IEEntity entity)
{
    return false;
}

void IEECSTransformSystem::onUpdateFrame(ECSOnUpdateEvent*)
{

}

void IEECSTransformSystem::onPostUpdateFrame()
{

}

void IEECSTransformSystem::onRenderFrame()
{

}
