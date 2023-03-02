#include "IEScene.h"
#include "GameStartEvent.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    meshManager(new IEMeshManager(this)),
    materialManager(new IEMaterialManager(this)),
    shaderManager(new IEShaderManager(this)),
    renderableManager(new IERenderableManager(this)),
    cameraManager(new IECameraManager(this)),
    ecs(new IEECS(this))
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(const GameStartEvent& event)
{
    meshManager->startup(event);
    materialManager->startup(event);
    shaderManager->startup(event);
    renderableManager->startup(event);
    cameraManager->startup(event);
    ecs->startup(event);
}

void IEScene::shutdown()
{
    ecs->shutdown();
    cameraManager->shutdown();
    renderableManager->shutdown();
    shaderManager->shutdown();
    materialManager->shutdown();
    meshManager->shutdown();
}

void IEScene::onUpdateFrame()
{
    ecs->onUpdateFrame();
}
