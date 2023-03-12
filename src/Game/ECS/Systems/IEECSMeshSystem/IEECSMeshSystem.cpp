#include "IEECSMeshSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"
#include "IEMeshManager.h"

IEECSMeshSystem::IEECSMeshSystem() :
    IEECSSystem(),
    data(),
    meshManager(nullptr)
{
    IEECSMeshSystem::attach(IEEntity(-1));
}

IEECSMeshSystem::~IEECSMeshSystem()
{
    meshManager = nullptr;
}

void IEECSMeshSystem::startup(const GameStartEvent& event)
{
    meshManager = &event.getScene().getMeshManager();
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

IEMesh& IEECSMeshSystem::getAttachedMesh(const int index)
{
    if(!indexBoundCheck(index))
        return meshManager->getValue(data.meshId[0]);

    return meshManager->getValue(data.meshId[index]);
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
