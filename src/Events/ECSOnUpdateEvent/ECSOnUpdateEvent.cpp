#include "ECSOnUpdateEvent.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSMeshSystem.h"

ECSOnUpdateEvent::ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                                   IEECSTransformSystem* transform_, IEECSMeshSystem* mesh_) :
    hierarchy(hierarchy_), input(input_), transform(transform_), mesh(mesh_)
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

const IEECSMeshSystem* ECSOnUpdateEvent::getMesh() const
{
    return mesh;
}
