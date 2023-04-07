#include "IERenderEngine.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECamera.h"

IERenderEngine IERenderEngine::mInstance;
IERenderEngine& IERenderEngine::instance() { return mInstance; }

IERenderEngine::IERenderEngine()
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

void IERenderEngine::onRenderFrame(IECamera* camera)
{
    if(!camera)
        return;

    auto& meshManager = IEScene::instance().getMeshManager();
    auto& materialManager = IEScene::instance().getMaterialManager();;
    auto& shaderManager = IEScene::instance().getShaderManager();;
    auto& renderableManager = IEScene::instance().getRenderableManager();;

    const auto* renderables = renderableManager.getResources();
    for(auto& i : *renderables)
    {
        auto* mesh = meshManager.value(i.second->getMeshId());
        auto* material = materialManager.value(i.second->getMaterialId());
        auto* shader = shaderManager.value(i.second->getShaderId());
        if(!mesh || !material || !shader)
            continue;

        prepareShader(*shader);
        prepareRenderable(*i.second);
        prepareViewProjection(*shader, *camera);
        prepareUniformData(*shader, *material);
        prepareUniformData(*shader, *i.second);
        draw(*i.second, *mesh);
        cleanup(*shader, *i.second);
    }
}

void IERenderEngine::prepareShader(IEShader& shader)
{
    shader.bind();
}

void IERenderEngine::prepareRenderable(IERenderable& renderable)
{
    renderable.checkForDirtyBuffers();
    renderable.bind();
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

void IERenderEngine::draw(IERenderable& renderable, IEMesh& mesh)
{
    QOpenGLExtraFunctions* glFunc = QOpenGLContext::currentContext()->extraFunctions();

    switch(renderable.getRenderType())
    {
    case IERenderable::RenderType::Vertex:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getPosVertices().size();
        glFunc->glDrawArrays(mode, 0, count);
        break;
    }
    case IERenderable::RenderType::Index:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getIndices().size();
        glFunc->glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        break;
    }
    case IERenderable::RenderType::I_Vertex:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getPosVertices().size();
        int instanceCount = renderable.shownInstanceCount();
        glFunc->glDrawArraysInstanced(mode, 0, count, instanceCount);
        break;
    }
    case IERenderable::RenderType::I_Index:
    {
        GLenum mode = renderable.getDrawMode();
        int count = mesh.getIndices().size();
        int instanceCount = renderable.shownInstanceCount();
        glFunc->glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, 0, instanceCount);
        break;
    }
    case IERenderable::RenderType::None: { break; }
    default: { break; }
    }
}

void IERenderEngine::cleanup(IEShader& shader, IERenderable& renderable)
{
    shader.release();
    renderable.release();
}
