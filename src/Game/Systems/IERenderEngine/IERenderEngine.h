#pragma once

#include "IEGameSystem.h"

class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IECamera;

class IERenderEngine : public IEGameSystem
{
    IERenderEngine();
    static IERenderEngine mInstance;

public:
    static IERenderEngine& instance();
    ~IERenderEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

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

