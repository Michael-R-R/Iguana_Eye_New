#include "IERenderEngine.h"
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include "RenderEngineStartEvent.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"
#include "IEECSCameraSystem.h"
#include "IECamera.h"

IERenderEngine::IERenderEngine() :
    IEObject(),
    meshManager(nullptr), materialManager(nullptr),
    shaderManager(nullptr), renderableManager(nullptr),
    cameraManager(nullptr), cameraSystem(nullptr)
{

}

IERenderEngine::~IERenderEngine()
{
    meshManager = nullptr;
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
    cameraManager = nullptr;
    cameraSystem = nullptr;
}

void IERenderEngine::startup(const RenderEngineStartEvent& event)
{
    auto& scene = event.getScene();
    meshManager = &scene.getMeshManager();
    materialManager = &scene.getMaterialManager();
    shaderManager = &scene.getShaderManager();
    renderableManager = &scene.getRenderableManager();
    cameraManager = &scene.getCameraManager();

    auto& ecs = scene.getECS();
    cameraSystem = ecs.getComponent<IEECSCameraSystem>(IEComponentType::Camera);
}

void IERenderEngine::shutdown()
{
    meshManager = nullptr;
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
    cameraManager = nullptr;
}

void IERenderEngine::onRenderFrame()
{
    auto camera = cameraSystem->getActiveCamera();

    auto renderables = renderableManager->getResourceContainer().getResources();
    for(auto* renderable : renderables)
    {
        auto mesh = meshManager->getValue(renderable->getMeshId());
        auto material = materialManager->getValue(renderable->getMaterialId());
        auto shader = shaderManager->getValue(renderable->getShaderId());
        if(!mesh || !material || !shader)
            continue;

        prepareShader(shader);
        prepareRenderable(renderable);
        prepareViewProjection(shader, camera);
        prepareUniformData(shader, material);
        prepareUniformData(shader, renderable);
        draw(renderable, mesh);
        cleanup(shader, renderable);
    }
}

void IERenderEngine::prepareShader(IEShader* shader)
{
    shader->bind();
}

void IERenderEngine::prepareRenderable(IERenderable* renderable)
{
    renderable->checkForDirtyBuffers();
    renderable->bind();
}

void IERenderEngine::prepareViewProjection(IEShader* shader, IECamera* camera)
{
    QMatrix4x4 viewProj = (camera) ? camera->getViewProjection() : QMatrix4x4();

    shader->setUniformValue("uViewProjection", viewProj);
}

void IERenderEngine::prepareUniformData(IEShader* shader, IEMaterial* material)
{
    material->bindUniformData(shader);
}

void IERenderEngine::prepareUniformData(IEShader* shader, IERenderable* renderable)
{
    renderable->bindUniformData(shader);
}

void IERenderEngine::draw(IERenderable* renderable, IEMesh* mesh)
{
    QOpenGLExtraFunctions* glFunc = QOpenGLContext::currentContext()->extraFunctions();

    switch(renderable->getRenderType())
    {
    case IERenderable::RenderType::Vertex:
    {
        GLenum mode = renderable->getDrawMode();
        int count = mesh->getPosVertices().size();
        glFunc->glDrawArrays(mode, 0, count);
        break;
    }
    case IERenderable::RenderType::Index:
    {
        GLenum mode = renderable->getDrawMode();
        int count = mesh->getIndices().size();
        glFunc->glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        break;
    }
    case IERenderable::RenderType::I_Vertex:
    {
        GLenum mode = renderable->getDrawMode();
        int count = mesh->getPosVertices().size();
        int instanceCount = renderable->shownInstanceCount();
        glFunc->glDrawArraysInstanced(mode, 0, count, instanceCount);
        break;
    }
    case IERenderable::RenderType::I_Index:
    {
        GLenum mode = renderable->getDrawMode();
        int count = mesh->getIndices().size();
        int instanceCount = renderable->shownInstanceCount();
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
