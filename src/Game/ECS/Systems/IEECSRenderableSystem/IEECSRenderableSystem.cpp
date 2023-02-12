#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSRenderableSystem::IEECSRenderableSystem() :
    IEECSSystem(),
    data()
{
    IEECSRenderableSystem::attach(IEEntity(-1));
}

int IEECSRenderableSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entityList.append(entity);
    data.renderableIdList.append(0);
    data.isRenderableList.append(false);

    return index;
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.renderableIdList[indexToRemove] = data.renderableIdList[lastIndex];
    data.isRenderableList[indexToRemove] = data.isRenderableList[lastIndex];

    data.entityList.removeLast();
    data.renderableIdList.removeLast();
    data.isRenderableList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSRenderableSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

void IEECSRenderableSystem::onPostUpdateFrame()
{
    // Not used
}

void IEECSRenderableSystem::onRenderFrame()
{
    // Not used
}

QVector<unsigned long long> IEECSRenderableSystem::massReplaceRenderableId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.renderableIdList.size(); i++)
    {
        if(data.renderableIdList[i] == oldId)
        {
            this->setRenderableId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSRenderableSystem::massPurgeRenderableId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.renderableIdList.size(); i++)
    {
        if(data.renderableIdList[i] == idToPurge)
        {
            this->setRenderableId(i, 0);
            result.append(i);
        }
    }

    return result;
}

unsigned long long IEECSRenderableSystem::getRenderableId(const int index)
{
    if(!indexBoundCheck(index))
        return data.renderableIdList[0];

    return data.renderableIdList[index];
}

bool IEECSRenderableSystem::getIsRenderable(const int index)
{
    if(!indexBoundCheck(index))
        return data.isRenderableList[0];

    return data.isRenderableList[index];
}

void IEECSRenderableSystem::setRenderableId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.renderableIdList[index] = val;
}

void IEECSRenderableSystem::setIsRenderable(const int index, const bool val)
{
    if(!indexBoundCheck(index))
        return;

    data.isRenderableList[index] = val;
}
