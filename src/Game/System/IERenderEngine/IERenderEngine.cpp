#include "IERenderEngine.h"
#include "QOpenGLContext"
#include <QOpenGLExtraFunctions>
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IETexture2DManager.h"
#include "IEUboManager.h"
#include "IECamera.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEUniformBufferObject.h"
#include "GLSViewProjection.h"

IERenderEngine::IERenderEngine(QObject* parent) :
    IESystem(parent),
    materialManager(nullptr),
    shaderManager(nullptr),
    renderableManager(nullptr),
    texture2DManager(nullptr)
{

}

IERenderEngine::~IERenderEngine()
{

}

void IERenderEngine::startup(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();
    materialManager = scene->getSystem<IEMaterialManager>();
    shaderManager = scene->getSystem<IEShaderManager>();
    renderableManager = scene->getSystem<IERenderableManager>();
    texture2DManager = scene->getSystem<IETexture2DManager>();
    uboManager = game.getSystem<IEUboManager>();
}

void IERenderEngine::shutdown(IEGame&)
{
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
    texture2DManager = nullptr;
    uboManager = nullptr;
}

void IERenderEngine::onPreRenderFrame()
{
    // TODO implement
}

void IERenderEngine::onRenderFrame(IECamera* camera)
{
    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    gl->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    if(!camera)
        return;

    prepareCamera(camera, uboManager->getVPBuffer());

    auto& renderables = renderableManager->getResources();
    for(auto* i : renderables)
    {
        auto* renderable = static_cast<IERenderable*>(i);
        auto* material = materialManager->value<IEMaterial>(renderable->getMaterialID());
        auto* shader = shaderManager->value<IEShader>(renderable->getShaderID());
        if(!material || !shader)
            continue;

        draw(shader, material, renderable);
    }
}

void IERenderEngine::onPostRenderFrame()
{
    // TODO implement
}

void IERenderEngine::prepareCamera(IECamera* camera, IEUniformBufferObject<GLSViewProjection>* ubo)
{
    ubo->setValue(0, camera->getVPStruct());
    ubo->handleSuballocate(0);
}

void IERenderEngine::draw(IEShader* shader, IEMaterial* material, IERenderable* renderable)
{
    shader->bind();

    const int nodeCount = renderable->getNodes().size();
    for(int i = 0; i < nodeCount; i++)
    {
        material->bindColors(i, *shader);
        material->bindTextures(i, *shader, *texture2DManager);

        renderable->draw(i);
    }
}
