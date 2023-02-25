#pragma once

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IEECS;

class RenderEngineStartEvent
{
    // Does not own these pointers
    const IEMeshManager* meshManager;
    const IEMaterialManager* materialManager;
    const IEShaderManager* shaderManager;
    const IERenderableManager* renderableManager;
    const IEECS* ecs;

public:
    RenderEngineStartEvent(IEMeshManager* meshManager_, IEMaterialManager* materialManager_,
                           IEShaderManager* shaderManager_, IERenderableManager* renderableManager_,
                           IEECS* ecs_);
    ~RenderEngineStartEvent();

    const IEMeshManager* getMeshManager() const;
    const IEMaterialManager* getMaterialManager() const;
    const IEShaderManager* getShaderManager() const;
    const IERenderableManager* getRenderableManager() const;
    const IEECS* getECS() const;
};

