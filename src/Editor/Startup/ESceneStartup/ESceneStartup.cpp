#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEEntityScript.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "EDefaultCamera.h"
#include "EDefaultMaterial.h"
#include "EGridRenderable.h"
#include "IEHash.h"
#include "IESerialize.h"
#include "IEGlslImporter.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    addDefaultCamera(event);
    addDefaultMaterial(event);
    addDefaultShader(event);
    buildGridRenderable(event);
    buildCameraEntity(event);
}

void ESceneStartup::addDefaultCamera(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto& cameraManager = scene.getCameraManager();

    QString path = "./resources/cameras/editor/default.iecam";
    unsigned long long id = IEHash::Compute(path);
    auto camera = std::make_unique<EDefaultCamera>(path, id);

    cameraManager.setDefaultResourceId(id);
    cameraManager.add(id, std::move(camera));
}

void ESceneStartup::addDefaultMaterial(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto& materialManager = scene.getMaterialManager();

    QString path = "./resources/materials/editor/default.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = std::make_unique<EDefaultMaterial>(path, id);

    materialManager.setDefaultResourceId(id);
    materialManager.add(id, std::move(material));
}

void ESceneStartup::addDefaultShader(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto& shaderManager = scene.getShaderManager();

    QString path = "./resources/shaders/editor/default.glsl";
    unsigned long long id = IEHash::Compute(path);
    auto shader = std::make_unique<IEShader>(path, id);
    IEGlslImporter::importGlsl(path, *shader);
    shader->build();

    shaderManager.setDefaultResourceId(id);
    shaderManager.add(id, std::move(shader));
}

void ESceneStartup::buildGridRenderable(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto& meshManager = scene.getMeshManager();
    auto& materialManager = scene.getMaterialManager();
    auto& shaderManager = scene.getShaderManager();
    auto& renderableManager = scene.getRenderableManager();

    unsigned long long id = IEHash::Compute("EGridRenderable");
    auto gridRenderable = std::make_unique<EGridRenderable>(id);
    gridRenderable->setup(meshManager, materialManager, shaderManager);

    renderableManager.add(id, std::move(gridRenderable));
}

void ESceneStartup::buildCameraEntity(const AppStartEvent& event)
{
    auto& scene = event.getGame()->getIEScene();
    auto& ecs = scene.getECS();
    auto* inputSystem = ecs.getComponent<IEECSInputSystem>("Input");
    auto* scriptSystem = ecs.getComponent<IEECSScriptSystem>("Script");
    auto* transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
    auto* cameraSystem = ecs.getComponent<IEECSCameraSystem>("Camera");
    auto& cameraManager = scene.getCameraManager();

    const unsigned long long cameraId = cameraManager.getDefaultResourceId();

    IEEntity entity = ecs.create();
    const int inputIndex = ecs.attachComponent(entity, "Input");
    inputSystem->setHasInput(inputIndex, true);

    const int scriptIndex = ecs.attachComponent(entity, "Script");
    const unsigned long long scriptId = IEHash::Compute("perspController");
    scriptSystem->addScript(scriptIndex, IEEntityScript("./resources/scripts/editor/perspController.lua", scriptId));
    scriptSystem->initalizeScript(scriptIndex, scriptId);
    scriptSystem->startScript(scriptIndex, scriptId);

    const int transformIndex = transformSystem->lookUpIndex(entity);
    transformSystem->setRotation(transformIndex, QVector3D(0.0f, 0.0f, -1.0f));

    const int cameraIndex = ecs.attachComponent(entity, "Camera");
    cameraSystem->setCameraId(cameraIndex, cameraId);
    cameraSystem->setActiveIndex(cameraIndex);
}
