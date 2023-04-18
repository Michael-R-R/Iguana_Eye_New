#include "IERenderEngine.h"
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include "ApplicationWindow.h"
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
    IEGameSystem(parent)
{

}

IERenderEngine::~IERenderEngine()
{

}

void IERenderEngine::startup(IEGame&)
{

}

void IERenderEngine::shutdown(IEGame&)
{

}

void IERenderEngine::initalize(IEGame&)
{

}

void IERenderEngine::reset(IEGame&)
{

}

void IERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    if(!camera)
        return;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* meshManager = scene->getMeshManager();
    auto* materialManager = scene->getMaterialManager();;
    auto* shaderManager = scene->getShaderManager();;
    auto* renderableManager = scene->getRenderableManager();;

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
