#include "IERenderEngine.h"
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>
#include "RenderEngineStartEvent.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"

IERenderEngine::IERenderEngine(QObject* parent) :
    IEObject(parent),
    meshManager(nullptr), materialManager(nullptr),
    shaderManager(nullptr), renderableManager(nullptr)
{

}

void IERenderEngine::startup(const RenderEngineStartEvent& event)
{
    meshManager = event.getMeshManager();
    materialManager = event.getMaterialManager();
    shaderManager = event.getShaderManager();
    renderableManager = event.getRenderableManager();
}

void IERenderEngine::shutdown()
{
    meshManager = nullptr;
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
}

void IERenderEngine::onRenderFrame()
{
    auto renderables = renderableManager->getResourceContainer()->getResources();
    for(auto* renderable : renderables)
    {
        if(!renderable->getIsRenderable())
            continue;

        auto mesh = meshManager->getValue(renderable->getMeshId());
        auto material = materialManager->getValue(renderable->getMaterialId());
        auto shader = shaderManager->getValue(renderable->getShaderId());
        if(!mesh || !material || !shader)
            continue;

        prepareShader(shader);
        //prepareViewProjection(shader, /* matrix here */);
        prepareUniformData(shader, material->getUniformData());
        prepareUniformData(shader, renderable->getUniformData());
        prepareRenderable(renderable);
        draw(renderable, mesh);
        cleanup(shader, renderable);
    }
}

void IERenderEngine::prepareShader(IEShader* shader)
{
    shader->bind();
}

void IERenderEngine::prepareViewProjection(IEShader* shader, const QMatrix4x4& matrix)
{
    shader->setUniformValue("uViewProjection", matrix);
}

void IERenderEngine::prepareUniformData(IEShader* shader, const IEUniform& data)
{
    data.bind(shader);
}

void IERenderEngine::prepareRenderable(IERenderable* renderable)
{
    renderable->bind();
}

void IERenderEngine::draw(IERenderable* renderable, IEMesh* mesh)
{
    QOpenGLExtraFunctions* glFunc = QOpenGLContext::currentContext()->extraFunctions();

    switch(renderable->getRenderType())
    {
    case IERenderable::RenderType::Vertex:
    {
        GLenum mode = renderable->getDrawType();
        int count = mesh->getPosVertices().size();
        glFunc->glDrawArrays(mode, 0, count);
        break;
    }
    case IERenderable::RenderType::Index:
    {
        GLenum mode = renderable->getDrawType();
        int count = mesh->getIndices().size();
        glFunc->glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        break;
    }
    case IERenderable::RenderType::I_Vertex:
    {
        GLenum mode = renderable->getDrawType();
        int count = mesh->getPosVertices().size();
        int instanceCount = renderable->instanceCount();
        glFunc->glDrawArraysInstanced(mode, 0, count, instanceCount);
        break;
    }
    case IERenderable::RenderType::I_Index:
    {
        GLenum mode = renderable->getDrawType();
        int count = mesh->getIndices().size();
        int instanceCount = renderable->instanceCount();
        glFunc->glDrawElementsInstanced(mode, count, GL_UNSIGNED_INT, 0, instanceCount);
        break;
    }
    case IERenderable::RenderType::None: { break; }
    default: { break; }
    }
}

void IERenderEngine::cleanup(IEShader* shader, IERenderable* renderable)
{
    shader->release();
    renderable->release();
}
