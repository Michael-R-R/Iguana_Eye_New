#pragma once

#include "IESystem.h"

class QOpenGLExtraFunctions;
class IEGame;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IEMaterial;
class IEShader;
class IERenderable;
class IECamera;

class IERenderEngine : public IESystem
{
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;

public:
    IERenderEngine(QObject* parent = nullptr);
    ~IERenderEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;

    void onPreRenderFrame();
    void onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera);
    void onPostRenderFrame();

private:
    void prepareViewProjection();
    void draw(IEShader* shader, IEMaterial* material, IERenderable* renderable);
};

