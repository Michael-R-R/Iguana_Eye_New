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

void IEScene::startup(IEGame& game)
{
    meshManager->startup(game);
    materialManager->startup(game);
    shaderManager->startup(game);
    renderableManager->startup(game);
    cameraManager->startup(game);
}

void IEScene::shutdown(IEGame& game)
{
    meshManager->shutdown(game);
    materialManager->shutdown(game);
    shaderManager->shutdown(game);
    renderableManager->shutdown(game);
    cameraManager->shutdown(game);
}

void IEScene::onSerialize(IEGame& game)
{
    meshManager->onSerialize(game);
    materialManager->onSerialize(game);
    shaderManager->onSerialize(game);
    renderableManager->onSerialize(game);
    cameraManager->onSerialize(game);
}

void IEScene::onDeserialize(IEGame& game)
{
    meshManager->onDeserialize(game);
    materialManager->onDeserialize(game);
    shaderManager->onDeserialize(game);
    renderableManager->onDeserialize(game);
    cameraManager->onDeserialize(game);
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

