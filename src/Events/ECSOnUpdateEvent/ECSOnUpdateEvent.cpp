#include "ECSOnUpdateEvent.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"

ECSOnUpdateEvent::ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                                   IEECSTransformSystem* transform_, IEECSMeshSystem* mesh_,
                                   IEECSMaterialSystem* material_, IEECSShaderSystem* shader_,
                                   IEECSRenderableSystem* renderable_) :
    hierarchy(hierarchy_), input(input_), transform(transform_), mesh(mesh_),
    material(material_), shader(shader_), renderable(renderable_)
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

const IEECSMaterialSystem* ECSOnUpdateEvent::getMaterial() const
{
    return material;
}

const IEECSShaderSystem* ECSOnUpdateEvent::getShader() const
{
    return shader;
}

const IEECSRenderableSystem* ECSOnUpdateEvent::getRenderable() const
{
    return renderable;
}
