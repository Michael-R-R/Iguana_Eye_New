#pragma once

#include "IEObject.h"

class IEMesh;
class IEMaterial;
class IEShader;
class IERenderable;
class IECamera;

class IERenderEngine : public IEObject
{

public:
    IERenderEngine();
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

