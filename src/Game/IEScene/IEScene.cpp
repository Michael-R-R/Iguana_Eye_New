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

QDataStream& operator<<(QDataStream& out, const IEScene& scene)
{
    out << *scene.getNameManager()
        << *scene.getMeshManager()
        << *scene.getMaterialManager()
        << *scene.getShaderManager()
        << *scene.getRenderableManager()
        << *scene.getECS();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEScene& scene)
{
    auto nameManager = scene.getNameManager();
    auto meshManager = scene.getMeshManager();
    auto materialManager = scene.getMaterialManager();
    auto shaderManager = scene.getShaderManager();
    auto renderableManager = scene.getRenderableManager();
    auto ecs = scene.getECS();

    in >> *nameManager
       >> *meshManager
       >> *materialManager
       >> *shaderManager
       >> *renderableManager
       >> *ecs;

    scene.setNameManager(nameManager);
    scene.setMeshManager(meshManager);
    scene.setMaterialManager(materialManager);
    scene.setShaderManager(shaderManager);
    scene.setRenderableManager(renderableManager);
    scene.setECS(ecs);

    return in;
}
