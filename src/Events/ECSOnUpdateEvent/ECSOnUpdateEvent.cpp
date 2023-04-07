#include "ECSOnUpdateEvent.h"
#include "IEECS.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"

ECSOnUpdateEvent::ECSOnUpdateEvent(IEECS* ecs) :
    name(nullptr), hierarchy(nullptr), input(nullptr),
    transform(nullptr), mesh(nullptr), material(nullptr),
    shader(nullptr), renderable(nullptr)
{
    name = ecs->getComponent<IEECSNameSystem>("Name");
    hierarchy = ecs->getComponent<IEECSHierarchySystem>("Hierarchy");
    input = ecs->getComponent<IEECSInputSystem>("Input");
    script = ecs->getComponent<IEECSScriptSystem>("Script");
    rigidbody3d = ecs->getComponent<IEECSRigidbody3DSystem>("Rigidbody3D");
    transform = ecs->getComponent<IEECSTransformSystem>("Transform");
    camera = ecs->getComponent<IEECSCameraSystem>("Camera");
    mesh = ecs->getComponent<IEECSMeshSystem>("Mesh");
    material = ecs->getComponent<IEECSMaterialSystem>("Material");
    shader = ecs->getComponent<IEECSShaderSystem>("Shader");
    renderable = ecs->getComponent<IEECSRenderableSystem>("Renderable");
}

ECSOnUpdateEvent::~ECSOnUpdateEvent()
{

}

IEECSNameSystem* ECSOnUpdateEvent::getName() const
{
    return name;
}

IEECSHierarchySystem* ECSOnUpdateEvent::getHierarchy() const
{
    return hierarchy;
}

IEECSInputSystem* ECSOnUpdateEvent::getInput() const
{
    return input;
}

IEECSScriptSystem* ECSOnUpdateEvent::getScript() const
{
    return script;
}

IEECSRigidbody3DSystem* ECSOnUpdateEvent::getRigidbody3D() const
{
    return rigidbody3d;
}

IEECSTransformSystem* ECSOnUpdateEvent::getTransform() const
{
    return transform;
}

IEECSCameraSystem* ECSOnUpdateEvent::getCamera() const
{
    return camera;
}

IEECSMeshSystem* ECSOnUpdateEvent::getMesh() const
{
    return mesh;
}

IEECSMaterialSystem* ECSOnUpdateEvent::getMaterial() const
{
    return material;
}

IEECSShaderSystem* ECSOnUpdateEvent::getShader() const
{
    return shader;
}

IEECSRenderableSystem* ECSOnUpdateEvent::getRenderable() const
{
    return renderable;
}
