#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"

IEScene IEScene::mInstance;
IEScene& IEScene::instance() { return mInstance; }

IEScene::IEScene() :
    meshManager(nullptr),
    materialManager(nullptr),
    shaderManager(nullptr),
    renderableManager(nullptr),
    cameraManager(nullptr)
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(IEGame&)
{
    meshManager = QSharedPointer<IEMeshManager>::create();
    materialManager = QSharedPointer<IEMaterialManager>::create();
    shaderManager = QSharedPointer<IEShaderManager>::create();
    renderableManager = QSharedPointer<IERenderableManager>::create();
    cameraManager = QSharedPointer<IECameraManager>::create();
}

void IEScene::shutdown(IEGame&)
{
    meshManager = nullptr;
    materialManager = nullptr;
    shaderManager = nullptr;
    renderableManager = nullptr;
    cameraManager = nullptr;
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

