#pragma once

class IEECS;
class IEECSNameSystem;
class IEECSHierarchySystem;
class IEECSInputSystem;
class IEECSTransformSystem;
class IEECSMeshSystem;
class IEECSMaterialSystem;
class IEECSShaderSystem;
class IEECSRenderableSystem;

class ECSOnUpdateEvent
{
    // Does not own these pointers
    IEECSNameSystem* name;
    IEECSHierarchySystem* hierarchy;
    IEECSInputSystem* input;
    IEECSTransformSystem* transform;
    IEECSMeshSystem* mesh;
    IEECSMaterialSystem* material;
    IEECSShaderSystem* shader;
    IEECSRenderableSystem* renderable;

public:
    ECSOnUpdateEvent(IEECS* ecs);
    ~ECSOnUpdateEvent();

    IEECSNameSystem* getName() const;
    IEECSHierarchySystem* getHierarchy() const;
    IEECSInputSystem* getInput() const;
    IEECSTransformSystem* getTransform() const;
    IEECSMeshSystem* getMesh() const;
    IEECSMaterialSystem* getMaterial() const;
    IEECSShaderSystem* getShader() const;
    IEECSRenderableSystem* getRenderable() const;
};

