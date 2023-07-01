#include "IEECSRenderableSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IERenderableManager.h"
#include "IERenderable.h"

IEECSRenderableSystem::IEECSRenderableSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSRenderableSystem).hash_code(), parent),
    moreData(), renderableManager(nullptr)
{
    IEECSRenderableSystem::attach(IEEntity(-1));
}

IEECSRenderableSystem::~IEECSRenderableSystem()
{

}

int IEECSRenderableSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    return IEECSResourceSystem::attach(entity);
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    return IEECSResourceSystem::detach(entity);
}

void IEECSRenderableSystem::startUp(const IEGame& game)
{
    renderableManager = game.getSystem<IEScene>()->getManager<IERenderableManager>();
}

void IEECSRenderableSystem::shutdown(const IEGame&)
{
    renderableManager = nullptr;
}

IERenderable* IEECSRenderableSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IERenderable>(index, renderableManager);
}

QDataStream& IEECSRenderableSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    IEECSResourceSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSRenderableSystem&>(obj);

    out << system.moreData;

    return out;
}

QDataStream& IEECSRenderableSystem::deserialize(QDataStream& in, Serializable& obj)
{
    IEECSResourceSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSRenderableSystem&>(obj);

    in >> system.moreData;

    return in;
}
