#pragma once

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
    const IEECSHierarchySystem* hierarchy;
    const IEECSInputSystem* input;
    const IEECSTransformSystem* transform;
    const IEECSMeshSystem* mesh;
    const IEECSMaterialSystem* material;
    const IEECSShaderSystem* shader;
    const IEECSRenderableSystem* renderable;

public:
    ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                     IEECSTransformSystem* transform_, IEECSMeshSystem* mesh_,
                     IEECSMaterialSystem* material_, IEECSShaderSystem* shader_,
                     IEECSRenderableSystem* renderable_);
    ~ECSOnUpdateEvent();

    const IEECSHierarchySystem* getHierarchy() const;
    const IEECSInputSystem* getInput() const;
    const IEECSTransformSystem* getTransform() const;
    const IEECSMeshSystem* getMesh() const;
    const IEECSMaterialSystem* getMaterial() const;
    const IEECSShaderSystem* getShader() const;
    const IEECSRenderableSystem* getRenderable() const;
};

