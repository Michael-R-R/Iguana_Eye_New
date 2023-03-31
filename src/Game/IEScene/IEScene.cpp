#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"

IEScene::IEScene() :
    meshManager(std::make_unique<IEMeshManager>()),
    materialManager(std::make_unique<IEMaterialManager>()),
    shaderManager(std::make_unique<IEShaderManager>()),
    renderableManager(std::make_unique<IERenderableManager>(*shaderManager)),
    cameraManager(std::make_unique<IECameraManager>())
{

}

IEScene::~IEScene()
{

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
