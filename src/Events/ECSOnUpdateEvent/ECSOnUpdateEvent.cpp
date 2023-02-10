#include "ECSOnUpdateEvent.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSTransformSystem.h"

ECSOnUpdateEvent::ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                                   IEECSTransformSystem* transform_) :
    hierarchy(hierarchy_), input(input_), transform(transform_)
{

}

ECSOnUpdateEvent::~ECSOnUpdateEvent()
{

}

const IEECSHierarchySystem* ECSOnUpdateEvent::getHierarchy() const
{
    return hierarchy;
}

const IEECSInputSystem* ECSOnUpdateEvent::getInput() const
{
    return input;
}

const IEECSTransformSystem* ECSOnUpdateEvent::getTransform() const
{
    return transform;
}
