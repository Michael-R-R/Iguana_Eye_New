#pragma once

class IEECS;
class IEECSNameSystem;
class IEECSHierarchySystem;
class IEECSInputSystem;
class IEECSScriptSystem;
class IEECSRigidbody3DSystem;
class IEECSTransformSystem;
class IEECSCameraSystem;
class IEECSMeshSystem;
class IEECSMaterialSystem;
class IEECSShaderSystem;
class IEECSRenderableSystem;

class ECSOnUpdateEvent
{
    IEECSNameSystem& name;
    IEECSHierarchySystem& hierarchy;
    IEECSInputSystem& input;
    IEECSScriptSystem& script;
    IEECSRigidbody3DSystem& rigidbody3d;
    IEECSTransformSystem& transform;
    IEECSCameraSystem& camera;
    IEECSMeshSystem& mesh;
    IEECSMaterialSystem& material;
    IEECSShaderSystem& shader;
    IEECSRenderableSystem& renderable;

public:
    ECSOnUpdateEvent(IEECS& ecs);
    ~ECSOnUpdateEvent();

    IEECSNameSystem& getName() const;
    IEECSHierarchySystem& getHierarchy() const;
    IEECSInputSystem& getInput() const;
    IEECSScriptSystem& getScript() const;
    IEECSRigidbody3DSystem& getRigidbody3D() const;
    IEECSTransformSystem& getTransform() const;
    IEECSCameraSystem& getCamera() const;
    IEECSMeshSystem& getMesh() const;
    IEECSMaterialSystem& getMaterial() const;
    IEECSShaderSystem& getShader() const;
    IEECSRenderableSystem& getRenderable() const;
};

