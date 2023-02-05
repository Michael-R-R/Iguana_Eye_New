#include "IEScene.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this)),
    meshManager(new IEMeshManager(this)),
    shaderManager(new IEShaderManager(this))
{

}

IEScene::~IEScene()
{

}

void IEScene::startup()
{
    nameManager->startup();
    meshManager->startup();
    shaderManager->startup();
}

void IEScene::shutdown()
{
    shaderManager->shutdown();
    meshManager->shutdown();
    nameManager->shutdown();
}

QDataStream& operator<<(QDataStream& out, const IEScene& scene)
{
    out << *scene.getNameManager()
        << *scene.getMeshManager()
        << *scene.getShaderManager();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEScene& scene)
{
    auto nameManager = scene.getNameManager();
    auto meshManager = scene.getMeshManager();
    auto shaderManager = scene.getShaderManager();

    in >> *nameManager
       >> *meshManager
       >> *shaderManager;

    scene.setNameManager(nameManager);
    scene.setMeshManager(meshManager);
    scene.setShaderManager(shaderManager);

    return in;
}
