#include "IEScene.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IEECS.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "IETexture2DManager.h"
#include "IEUboManager.h"
#include "IERenderEngine.h"

IEScene::IEScene(QObject* parent) :
    IESystem(parent),
    systems(), systemIndices()
{

}

IEScene::~IEScene()
{

}

void IEScene::startup(IEGame& game)
{
    appendSystem<IEScriptEngine>(new IEScriptEngine(this));
    appendSystem<IEPhysicsEngine>(new IEPhysicsEngine(this));
    appendSystem<IEECS>(new IEECS(this));
    appendSystem<IEMaterialManager>(new IEMaterialManager(this));
    appendSystem<IEShaderManager>(new IEShaderManager(this));
    appendSystem<IERenderableManager>(new IERenderableManager(this));
    appendSystem<IECameraManager>(new IECameraManager(this));
    appendSystem<IETexture2DManager>(new IETexture2DManager(this));
    appendSystem<IEUboManager>(new IEUboManager(this));
    appendSystem<IERenderEngine>(new IERenderEngine(this));

    foreach(auto* i, systems)
    {
        i->startup(game);
    }
}

void IEScene::shutdown(IEGame& game)
{
    for(int i = systems.size() - 1; i >= 0; i--)
    {
        auto* system = systems[i];
        system->shutdown(game);
        delete system;
        system = nullptr;
    }

    systems.clear();
    systemIndices.clear();
}

void IEScene::onSerialize(IEGame& game)
{
    foreach(auto* i, systems)
    {
        i->onSerialize(game);
    }
}

void IEScene::onDeserialize(IEGame& game)
{
    foreach(auto* i, systems)
    {
        i->onDeserialize(game);
    }
}

QDataStream& IEScene::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& scene = static_cast<const IEScene&>(obj);

    foreach (auto* i, scene.systems)
    {
        out << *i;
    }

    out << scene.systemIndices;

    return out;
}

QDataStream& IEScene::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& scene = static_cast<IEScene&>(obj);

    foreach (auto* i, scene.systems)
    {
        in >> *i;
    }

    in >> scene.systemIndices;

    return in;
}

