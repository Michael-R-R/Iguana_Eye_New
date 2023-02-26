#include "IEECSMaterialSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSMaterialSystem::IEECSMaterialSystem() :
    IEECSSystem(),
    data()
{
    IEECSMaterialSystem::attach(IEEntity(-1));
}

void IEECSMaterialSystem::startup(const GameStartEvent&)
{
    // Not used
}

int IEECSMaterialSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = entityMap.size();

    entityMap[entity] = index;

    data.entityList.append(entity);
    data.materialIdList.append(0);

    return index;
}

bool IEECSMaterialSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.materialIdList[indexToRemove] = data.materialIdList[lastIndex];

    data.entityList.removeLast();
    data.materialIdList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSMaterialSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QVector<unsigned long long> IEECSMaterialSystem::massReplaceMaterialId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.materialIdList.size(); i++)
    {
        if(data.materialIdList[i] == oldId)
        {
            this->setMaterialId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSMaterialSystem::massPurgeMaterialId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.materialIdList.size(); i++)
    {
        if(data.materialIdList[i] == idToPurge)
        {
            this->setMaterialId(i, 0);
            result.append(i);
        }
    }

    return result;
}

unsigned long long IEECSMaterialSystem::getMaterialId(const int index)
{
    if(!indexBoundCheck(index))
        return data.materialIdList[0];

    return data.materialIdList[index];
}

void IEECSMaterialSystem::setMaterialId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.materialIdList[index] = val;
}
