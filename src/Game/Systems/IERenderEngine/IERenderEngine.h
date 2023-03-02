#pragma once

#include <QMatrix4x4>

#include "IEObject.h"

class RenderEngineStartEvent;
class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;
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
    const IECameraManager* cameraManager;

public:
    IERenderEngine(QObject* parent = nullptr);
    ~IERenderEngine() {}

    void startup(const RenderEngineStartEvent& event);
    void shutdown();

    void onRenderFrame();

private:
    void prepareShader(IEShader* shader);
    void prepareViewProjection(IEShader* shader, IECamera* camera);
    void prepareUniformData(IEShader* shader, IEMaterial* material);
    void prepareUniformData(IEShader* shader, IERenderable* renderable);
    void prepareRenderable(IERenderable* renderable);
    void draw(IERenderable* renderable, IEMesh* mesh);
    void cleanup(IEShader* shader, IERenderable* renderable);
};

