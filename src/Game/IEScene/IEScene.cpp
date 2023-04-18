#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"

IEScene::IEScene(QObject* parent) :
    IEGameSystem(parent),
    meshManager(new IEMeshManager(this)),
    materialManager(new IEMaterialManager(this)),
    shaderManager(new IEShaderManager(this)),
    renderableManager(new IERenderableManager(this)),
    cameraManager(new IECameraManager(this))
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(IEGame&)
{
    meshManager->startup();
    materialManager->startup();
    shaderManager->startup();
    renderableManager->startup();
    cameraManager->startup();
}

void IEScene::shutdown(IEGame&)
{
    meshManager->shutdown();
    materialManager->shutdown();
    shaderManager->shutdown();
    renderableManager->shutdown();
    cameraManager->shutdown();
}

void IEScene::initalize(IEGame&)
{

}

void IEScene::reset(IEGame& game)
{
    shutdown(game);
    startup(game);
}

QDataStream& IEScene::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& scene = static_cast<const IEScene&>(obj);

    out << *scene.meshManager
        << *scene.materialManager
        << *scene.shaderManager
        << *scene.renderableManager
        << *scene.cameraManager;

    return out;
}

QDataStream& IEScene::deserialize(QDataStream& in, Serializable& obj)
{
    auto& scene = static_cast<IEScene&>(obj);

    in >> *scene.meshManager
       >> *scene.materialManager
       >> *scene.shaderManager
       >> *scene.renderableManager
       >> *scene.cameraManager;

    return in;
}

