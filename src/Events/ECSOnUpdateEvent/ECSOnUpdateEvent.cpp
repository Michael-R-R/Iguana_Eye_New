#include "ECSOnUpdateEvent.h"
#include "IEECS.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"

ECSOnUpdateEvent::ECSOnUpdateEvent(IEECS* ecs) :
    name(nullptr), hierarchy(nullptr), input(nullptr),
    transform(nullptr), mesh(nullptr), material(nullptr),
    shader(nullptr), renderable(nullptr)
{
    name = ecs->getComponent<IEECSNameSystem>(IEComponentType::Name);
    hierarchy = ecs->getComponent<IEECSHierarchySystem>(IEComponentType::Hierarchy);
    input = ecs->getComponent<IEECSInputSystem>(IEComponentType::Input);
    transform = ecs->getComponent<IEECSTransformSystem>(IEComponentType::Transform);
    mesh = ecs->getComponent<IEECSMeshSystem>(IEComponentType::Mesh);
    material = ecs->getComponent<IEECSMaterialSystem>(IEComponentType::Material);
    shader = ecs->getComponent<IEECSShaderSystem>(IEComponentType::Shader);
    renderable = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);
}

ECSOnUpdateEvent::~ECSOnUpdateEvent()
{
    name = nullptr;
    hierarchy = nullptr;
    input = nullptr;
    transform = nullptr;
    mesh = nullptr;
    material = nullptr;
    shader = nullptr;
    renderable = nullptr;
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

IEECSTransformSystem* ECSOnUpdateEvent::getTransform() const
{
    return transform;
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
