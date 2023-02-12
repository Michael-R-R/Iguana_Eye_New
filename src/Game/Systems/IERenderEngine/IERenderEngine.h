#pragma once

#include <QMatrix4x4>

#include "IEObject.h"

class GameStartEvent;
class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IEShader;
class IEUniform;
class IERenderable;
class IEMesh;

class IERenderEngine : public IEObject
{
     // Does not own these pointers
    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;

public:
    IERenderEngine(QObject* parent = nullptr);
    ~IERenderEngine() {}

    void startup(const GameStartEvent& event);
    void shutdown();

    void onRenderFrame();

private:
    void prepareShader(IEShader* shader);
    void prepareViewProjection(IEShader* shader, const QMatrix4x4& matrix);
    void prepareUniformData(IEShader* shader, const IEUniform& data);
    void prepareRenderable(IERenderable* renderable);
    void draw(IERenderable* renderable, IEMesh* mesh);
    void cleanup(IEShader* shader, IERenderable* renderable);
};

