#include "IEECSShaderSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSShaderSystem::IEECSShaderSystem() :
    IEECSSystem(),
    data()
{
    IEECSShaderSystem::attach(IEEntity(-1));
}

int IEECSShaderSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entityList.append(entity);
    data.shaderIdList.append(0);

    return index;
}

bool IEECSShaderSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.shaderIdList[indexToRemove] = data.shaderIdList[lastIndex];

    data.entityList.removeLast();
    data.entityList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSShaderSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QVector<unsigned long long> IEECSShaderSystem::massReplaceShaderId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.shaderIdList.size(); i++)
    {
        if(data.shaderIdList[i] == oldId)
        {
            this->setShaderId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSShaderSystem::massPurgeShaderId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.shaderIdList.size(); i++)
    {
        if(data.shaderIdList[i] == idToPurge)
        {
            this->setShaderId(i, 0);
            result.append(i);
        }
    }

    return result;
}

unsigned long long IEECSShaderSystem::getShaderId(const int index)
{
    if(!indexBoundCheck(index))
        return data.shaderIdList[0];

    return data.shaderIdList[index];
}

void IEECSShaderSystem::setShaderId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.shaderIdList[index] = val;
}
