#pragma once

#include "IEGameSystem.h"

class QOpenGLExtraFunctions;
class IEGame;
class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IECamera;

class IERenderEngine : public IEGameSystem
{

public:
    IERenderEngine(QObject* parent = nullptr);
    ~IERenderEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    void onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera);

private:
    void prepareShader(IEShader& shader);
    void prepareRenderable(IERenderable& renderable);
    void prepareViewProjection(IEShader& shader, IECamera& camera);
    void prepareUniformData(IEShader& shader, IEMaterial& material);
    void prepareUniformData(IEShader& shader, IERenderable& renderable);
    void draw(QOpenGLExtraFunctions* glFunc, IERenderable& renderable, IEMesh& mesh);
    void cleanup(IEShader& shader, IERenderable& renderable);
};

