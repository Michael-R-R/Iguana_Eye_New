#include "IEScene.h"
#include "GameStartEvent.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "IEECS.h"

IEScene::IEScene() :
    meshManager(std::make_unique<IEMeshManager>()),
    materialManager(std::make_unique<IEMaterialManager>()),
    shaderManager(std::make_unique<IEShaderManager>()),
    renderableManager(std::make_unique<IERenderableManager>()),
    cameraManager(std::make_unique<IECameraManager>()),
    ecs(std::make_unique<IEECS>())
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

QDataStream& IEScene::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& scene = static_cast<const IEScene&>(obj);

    out << *scene.meshManager
        << *scene.materialManager
        << *scene.shaderManager
        << *scene.renderableManager
        << *scene.cameraManager
        << *scene.ecs;

    return out;
}

QDataStream& IEScene::deserialize(QDataStream& in, Serializable& obj)
{
    auto& scene = static_cast<IEScene&>(obj);

    in >> *scene.meshManager
       >> *scene.materialManager
       >> *scene.shaderManager
       >> *scene.renderableManager
       >> *scene.cameraManager
       >> *scene.ecs;

    return in;
}
