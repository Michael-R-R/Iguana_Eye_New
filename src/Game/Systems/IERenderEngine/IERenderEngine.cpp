#include "IERenderEngine.h"
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECamera.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"

IERenderEngine::IERenderEngine(QObject* parent) :
    IEGameSystem(parent),
    meshManager(nullptr), materialManager(nullptr),
    shaderManager(nullptr), renderableManager(nullptr)
{

}

IERenderEngine::~IERenderEngine()
{

}

void IERenderEngine::startup(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();
    meshManager = scene->getManager<IEMeshManager>();
    materialManager = scene->getManager<IEMaterialManager>();
    shaderManager = scene->getManager<IEShaderManager>();
    renderableManager = scene->getManager<IERenderableManager>();
}

void IERenderEngine::shutdown(IEGame&)
{
    meshManager = nullptr;
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
}

void IERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    glFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    if(!camera)
        return;

    auto& renderables = renderableManager->getResources();
    for(auto* i : renderables)
    {
        auto* renderable = static_cast<IERenderable*>(i);
        auto* mesh = meshManager->value<IEMesh>(renderable->getMeshId());
        auto* material = materialManager->value<IEMaterial>(renderable->getMaterialId());
        auto* shader = shaderManager->value<IEShader>(renderable->getShaderId());
        if(!mesh || !material || !shader)
            continue;

        prepareShader(*shader);
        prepareRenderable(*renderable);
        prepareViewProjection(*shader, *camera);
        prepareUniformData(*shader, *material);
        prepareUniformData(*shader, *renderable);
        draw(glFunc, *renderable, *mesh);
        cleanup(*shader, *renderable);
    }
}

void IERenderEngine::prepareShader(IEShader& shader)
{
    shader.bind();
}

void IERenderEngine::prepareRenderable(IERenderable& renderable)
{
    renderable.bind();
    renderable.checkForDirtyBuffers();
}

void IERenderEngine::prepareViewProjection(IEShader& shader, IECamera& camera)
{
    shader.setUniformValue("uViewProjection", camera.getViewProjection());
}

void IERenderEngine::prepareUniformData(IEShader& shader, IEMaterial& material)
{
    material.bindUniformData(shader);
}

void IERenderEngine::prepareUniformData(IEShader& shader, IERenderable& renderable)
{
    renderable.bindUniformData(shader);
}

void IERenderEngine::draw(QOpenGLExtraFunctions* glFunc, IERenderable& renderable, IEMesh& mesh)
{
    switch(renderable.getRenderMode())
    {
    case IERenderable::RenderMode::Vertex:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getPosVertices().size();
        glFunc->glDrawArrays(mode, 0, count);
        break;
    }
    case IERenderable::RenderMode::Index:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getIndices().size();
        glFunc->glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        break;
    }
    case IERenderable::RenderMode::I_Vertex:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getPosVertices().size();
        int instanceCount = renderable.shownInstanceCount();
        glFunc->glDrawArraysInstanced(mode, 0, count, instanceCount);
        break;
    }
    case IERenderable::RenderMode::I_Index:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getIndices().size();
        int instanceCount = renderable.shownInstanceCount();
        glFunc->glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, 0, instanceCount);
        break;
    }
    case IERenderable::RenderMode::None: { break; }
    default: { break; }
    }
}

void IERenderEngine::cleanup(IEShader& shader, IERenderable& renderable)
{
    shader.release();
    renderable.release();
}
