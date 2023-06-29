#include "IEECSMaterialSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterial.h"
#include "IEMaterialManager.h"

IEECSMaterialSystem::IEECSMaterialSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSMaterialSystem).hash_code(), parent),
    materialManager(nullptr)
{
    IEECSMaterialSystem::attach(IEEntity(-1));
}

IEECSMaterialSystem::~IEECSMaterialSystem()
{

}

void IEECSMaterialSystem::startUp(const IEGame& game)
{
    materialManager = game.getSystem<IEScene>()->getMaterialManager();
}

void IEECSMaterialSystem::shutdown(const IEGame& game)
{
    materialManager = nullptr;
}

IEMaterial* IEECSMaterialSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IEMaterial>(index, materialManager);
}

QDataStream& IEECSMaterialSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEECSResourceSystem::serialize(out, obj);
}

QDataStream& IEECSMaterialSystem::deserialize(QDataStream& in, Serializable& obj)
{
    return IEECSResourceSystem::deserialize(in, obj);
}
