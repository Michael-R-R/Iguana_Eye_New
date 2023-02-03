#include "IEScene.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this))
{

}

IEScene::~IEScene()
{

}

QDataStream& operator<<(QDataStream& out, const IEScene& scene)
{
    out << *scene.getNameManager();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEScene& scene)
{
    delete scene.getNameManager();

    auto nameManager = new IENameManager(&scene);

    in >> *nameManager;

    scene.setNameManager(nameManager);

    return in;
}
