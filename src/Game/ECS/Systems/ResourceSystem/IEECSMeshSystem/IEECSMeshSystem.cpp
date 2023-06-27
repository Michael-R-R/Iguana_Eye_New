#include "IEECSMeshSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMesh.h"

IEECSMeshSystem::IEECSMeshSystem(QObject* parent) :
    IEECSResourceSystem(parent),
    meshManager(nullptr)
{
    IEECSMeshSystem::attach(IEEntity(-1));
}

IEECSMeshSystem::~IEECSMeshSystem()
{

}

void IEECSMeshSystem::startUp(const IEGame& game)
{
    meshManager = game.getScene()->getMeshManager();
}

IEMesh* IEECSMeshSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IEMesh>(index, meshManager);
}

QDataStream& IEECSMeshSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEECSResourceSystem::serialize(out, obj);
}

QDataStream& IEECSMeshSystem::deserialize(QDataStream& in, Serializable& obj)
{
    return IEECSResourceSystem::deserialize(in, obj);
}
