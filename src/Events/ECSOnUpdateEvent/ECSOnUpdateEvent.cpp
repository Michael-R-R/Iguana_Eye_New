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
    name = ecs->getComponent<IEECSNameSystem>();
    hierarchy = ecs->getComponent<IEECSHierarchySystem>();
    input = ecs->getComponent<IEECSInputSystem>();
    script = ecs->getComponent<IEECSScriptSystem>();
    rigidbody3d = ecs->getComponent<IEECSRigidbody3DSystem>();
    transform = ecs->getComponent<IEECSTransformSystem>();
    camera = ecs->getComponent<IEECSCameraSystem>();
    mesh = ecs->getComponent<IEECSMeshSystem>();
    material = ecs->getComponent<IEECSMaterialSystem>();
    shader = ecs->getComponent<IEECSShaderSystem>();
    renderable = ecs->getComponent<IEECSRenderableSystem>();
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
