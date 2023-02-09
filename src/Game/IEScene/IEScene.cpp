#include "IEScene.h"
#include "GameStartEvent.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this)),
    meshManager(new IEMeshManager(this)),
    materialManager(new IEMaterialManager(this)),
    shaderManager(new IEShaderManager(this)),
    renderableManager(new IERenderableManager(this)),
    ecs(new IEECS(this))
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(const GameStartEvent& event)
{
    nameManager->startup(event);
    meshManager->startup(event);
    materialManager->startup(event);
    shaderManager->startup(event);
    renderableManager->startup(event);
    ecs->startup(event);
}

void IEScene::shutdown()
{
    ecs->shutdown();
    renderableManager->shutdown();
    shaderManager->shutdown();
    materialManager->shutdown();
    meshManager->shutdown();
    nameManager->shutdown();
}
