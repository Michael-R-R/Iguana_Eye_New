#include "IEECSMeshSystem.h"
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

    data.entityList.append(entity);
    data.meshIdList.append(0);

    return index;
}

bool IEECSMeshSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.meshIdList[indexToRemove] = data.meshIdList[lastIndex];

    data.entityList.removeLast();
    data.meshIdList.removeLast();

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

    for(int i = 1; i < data.meshIdList.size(); i++)
    {
        if(data.meshIdList[i] == oldId)
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

    for(int i = 1; i < data.meshIdList.size(); i++)
    {
        if(data.meshIdList[i] == idToPurge)
        {
            this->setMeshId(i, 0);
            result.append(i);
        }
    }

    return result;
}

unsigned long long IEECSMeshSystem::getMeshId(const int index)
{
    if(!indexBoundCheck(index))
        return data.meshIdList[0];

    return data.meshIdList[index];
}

void IEECSMeshSystem::setMeshId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.meshIdList[index] = val;
}
