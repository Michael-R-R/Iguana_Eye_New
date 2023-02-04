#include "IEScene.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this)),
    shaderManager(new IEShaderManager(this))
{

}

IEScene::~IEScene()
{

}

QDataStream& operator<<(QDataStream& out, const IEScene& scene)
{
    out << *scene.getNameManager() << *scene.getShaderManager();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEScene& scene)
{
    auto nameManager = scene.getNameManager();
    auto shaderManager = scene.getShaderManager();

    in >> *nameManager >> *shaderManager;

    scene.setNameManager(nameManager);
    scene.setShaderManager(shaderManager);

    return in;
}
