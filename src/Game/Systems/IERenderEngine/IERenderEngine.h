#pragma once

#include "IEObject.h"

class IEScene;
class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IECamera;

class IERenderEngine : public IEObject
{
     // Does not own these pointers
    const IEMeshManager* meshManager;
    const IEMaterialManager* materialManager;
    const IEShaderManager* shaderManager;
    const IERenderableManager* renderableManager;

public:
    IERenderEngine(IEScene& scene);
    ~IERenderEngine();

    void onRenderFrame(IECamera* camera);

private:
    void prepareShader(IEShader& shader);
    void prepareRenderable(IERenderable& renderable);
    void prepareViewProjection(IEShader& shader, IECamera& camera);
    void prepareUniformData(IEShader& shader, IEMaterial& material);
    void prepareUniformData(IEShader& shader, IERenderable& renderable);
    void draw(IERenderable& renderable, IEMesh& mesh);
    void cleanup(IEShader& shader, IERenderable& renderable);
};

