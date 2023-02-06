#include "IEScene.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this)),
    meshManager(new IEMeshManager(this)),
    materialManager(new IEMaterialManager(this)),
    shaderManager(new IEShaderManager(this)),
    renderableManager(new IERenderableManager(this))
{

}

IEScene::~IEScene()
{

}

void IEScene::startup()
{
    nameManager->startup();
    meshManager->startup();
    materialManager->startup();
    shaderManager->startup();
    renderableManager->startup();
}

void IEScene::shutdown()
{
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
        << *scene.getRenderableManager();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEScene& scene)
{
    auto nameManager = scene.getNameManager();
    auto meshManager = scene.getMeshManager();
    auto materialManager = scene.getMaterialManager();
    auto shaderManager = scene.getShaderManager();
    auto renderableManager = scene.getRenderableManager();

    in >> *nameManager
       >> *meshManager
       >> *materialManager
       >> *shaderManager
       >> *renderableManager;

    scene.setNameManager(nameManager);
    scene.setMeshManager(meshManager);
    scene.setMaterialManager(materialManager);
    scene.setShaderManager(shaderManager);
    scene.setRenderableManager(renderableManager);

    return in;
}
