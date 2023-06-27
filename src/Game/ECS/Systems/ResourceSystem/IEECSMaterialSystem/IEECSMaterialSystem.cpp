#include "IEECSMaterialSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterial.h"
#include "IEMaterialManager.h"

IEECSMaterialSystem::IEECSMaterialSystem(QObject* parent) :
    IEECSResourceSystem(parent),
    materialManager(nullptr)
{
    IEECSMaterialSystem::attach(IEEntity(-1));
}

IEECSMaterialSystem::~IEECSMaterialSystem()
{

}

void IEECSMaterialSystem::startUp(const IEGame& game)
{
    materialManager = game.getScene()->getMaterialManager();
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
