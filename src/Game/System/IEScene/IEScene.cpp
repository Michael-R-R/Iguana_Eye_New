#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"

IEScene::IEScene(QObject* parent) :
    IESystem(parent),
    managers(), managerIndices()
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(IEGame& game)
{
    appendManager<IEMeshManager>(new IEMeshManager(this));
    appendManager<IEMaterialManager>(new IEMaterialManager(this));
    appendManager<IEShaderManager>(new IEShaderManager(this));
    appendManager<IERenderableManager>(new IERenderableManager(this));
    appendManager<IECameraManager>(new IECameraManager(this));

    foreach (auto* i, managers)
    {
        i->startup(game);
    }
}

void IEScene::shutdown(IEGame& game)
{
    foreach (auto* i, managers)
    {
        i->shutdown(game);
        delete i;
        i = nullptr;
    }
}

void IEScene::onSerialize(IEGame& game)
{
    foreach (auto* i, managers)
    {
        i->onSerialize(game);
    }
}

void IEScene::onDeserialize(IEGame& game)
{
    foreach (auto* i, managers)
    {
        i->onDeserialize(game);
    }
}

bool IEScene::doesManagerExist(const size_t key) const
{
    return managerIndices.contains(key);
}

QDataStream& IEScene::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& scene = static_cast<const IEScene&>(obj);

    foreach (auto* i, scene.managers)
    {
        out << *i;
    }

    out << scene.managerIndices;

    return out;
}

QDataStream& IEScene::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& scene = static_cast<IEScene&>(obj);

    foreach (auto* i, scene.managers)
    {
        in >> *i;
    }

    in >> scene.managerIndices;

    return in;
}

