#include "IEECSMeshSystem.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "ECSOnUpdateEvent.h"

IEECSMeshSystem::IEECSMeshSystem() :
    IEECSSystem(),
    data()
{
    IEECSMeshSystem::attach(IEEntity(-1));
}

IEECSMeshSystem::~IEECSMeshSystem()
{

}

int IEECSMeshSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.meshId.append(0);

    return index;
}

bool IEECSMeshSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.meshId[indexToRemove] = data.meshId[lastIndex];

    data.entity.removeLast();
    data.meshId.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSMeshSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QVector<unsigned long long> IEECSMeshSystem::massReplaceMeshId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.meshId.size(); i++)
    {
        if(data.meshId[i] == oldId)
        {
            this->setMeshId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSMeshSystem::massPurgeMeshId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.meshId.size(); i++)
    {
        if(data.meshId[i] == idToPurge)
        {
            this->setMeshId(i, 0);
            result.append(i);
        }
    }

    return result;
}

QSharedPointer<IEMesh> IEECSMeshSystem::getAttachedMesh(const int index)
{
    if(!indexBoundCheck(index))
        return nullptr;

    auto& meshManager = IEScene::instance().getMeshManager();

    return meshManager.value(data.meshId[index]);
}

unsigned long long IEECSMeshSystem::getMeshId(const int index)
{
    if(!indexBoundCheck(index))
        return data.meshId[0];

    return data.meshId[index];
}

void IEECSMeshSystem::setMeshId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.meshId[index] = val;
}

QDataStream& IEECSMeshSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSMeshSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSMeshSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSMeshSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
