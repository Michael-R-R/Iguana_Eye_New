#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEHash.h"
#include "IESerialize.h"
#include "EDefaultCamera.h"
#include "EDefaultMaterial.h"
#include "EGridRenderable.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    addDefaultCamera(event);
    addDefaultMaterial(event);
    addDefaultShader(event);
    buildGridRenderable(event);
}

void ESceneStartup::addDefaultCamera(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto cameraManager = scene.getCameraManager();

    QString path = "./resources/cameras/editor/default.iecam";
    unsigned long long id = IEHash::Compute(path);
    auto camera = new EDefaultCamera(path, id);

    cameraManager->setDefaultResourceId(id);
    cameraManager->add(id, camera);
}

void ESceneStartup::addDefaultMaterial(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto materialManager = scene.getMaterialManager();

    QString path = "./resources/materials/editor/default.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new EDefaultMaterial(path, id);

    materialManager->setDefaultResourceId(id);
    materialManager->add(id, material);
}

void ESceneStartup::addDefaultShader(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto shaderManager = scene.getShaderManager();

    QString path = "./resources/shaders/editor/default.glsl";
    unsigned long long id = IEHash::Compute(path);
    auto shader = new IEShader(path, id);
    IEGlslImporter::importGlsl(path, shader);
    shader->build();

    shaderManager->setDefaultResourceId(id);
    shaderManager->add(id, shader);
}

void ESceneStartup::buildGridRenderable(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto meshManager = scene.getMeshManager();
    auto materialManager = scene.getMaterialManager();
    auto shaderManager = scene.getShaderManager();
    auto renderableManager = scene.getRenderableManager();

    unsigned long long id = IEHash::Compute("EGridRenderable");
    auto gridRenderable = new EGridRenderable(id);
    gridRenderable->setup(meshManager, materialManager, shaderManager);

    renderableManager->add(id, gridRenderable);
}
