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
    materialManager = scene->getManager<IEMaterialManager>();
    shaderManager = scene->getManager<IEShaderManager>();
    renderableManager = scene->getManager<IERenderableManager>();
    texture2DManager = scene->getManager<IETexture2DManager>();
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

    //auto* uboVP = uboManager->getVPBuffer();
    //uboVP->setValue(0, camera->getViewProjection());
    //uboVP->handleSuballocate(0);

    auto& renderables = renderableManager->getResources();
    for(auto* i : renderables)
    {
        auto* renderable = static_cast<IERenderable*>(i);
        auto* material = materialManager->value<IEMaterial>(renderable->getMaterialId());
        auto* shader = shaderManager->value<IEShader>(renderable->getShaderId());
        if(!material || !shader)
            continue;

        shader->bind();
        shader->setMat4("vp", camera->getViewProjection());

        draw(shader, material, renderable);
    }
}

void IERenderEngine::onPostRenderFrame()
{
    // TODO implement
}

void IERenderEngine::draw(IEShader* shader, IEMaterial* material, IERenderable* renderable)
{
    //shader->bind();

    auto& maChildren = material->getChildren();
    auto& rChildren = renderable->getChildren();
    for(int i = 0; i < rChildren.size(); i++)
    {
        auto& materials = maChildren[i]->getMaterials();
        auto& renderables = rChildren[i]->getRenderables();
        for(int j = 0; j < renderables.size(); j++)
        {
            materials[j]->bindColors(*shader);
            materials[j]->bindTextures(*shader, *texture2DManager);
            renderables[j]->draw();
        }
    }
}
