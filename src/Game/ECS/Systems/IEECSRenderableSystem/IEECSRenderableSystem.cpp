#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

IEECSRenderableSystem::IEECSRenderableSystem() :
    IEECSSystem(),
    data(),
    shownRenderableList(),
    hiddenRenderableList()
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
    data.shownInstanceIndexList.append(-1);
    data.hiddenInstanceIndexList.append(-1);
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
    data.shownInstanceIndexList[indexToRemove] = data.shownInstanceIndexList[lastIndex];
    data.hiddenInstanceIndexList[indexToRemove] = data.hiddenInstanceIndexList[lastIndex];
    data.isRenderableList[indexToRemove] = data.isRenderableList[lastIndex];

    data.entityList.removeLast();
    data.renderableIdList.removeLast();
    data.shownInstanceIndexList.removeLast();
    data.hiddenInstanceIndexList.removeLast();
    data.isRenderableList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSRenderableSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

int IEECSRenderableSystem::shownInstanceCount(const unsigned long long id) const
{
    if(!shownRenderableList.contains(id))
        return -1;

    return shownRenderableList[id].size();
}

int IEECSRenderableSystem::hiddenInstanceCount(const unsigned long long id) const
{
    if(!hiddenRenderableList.contains(id))
        return -1;

    return hiddenRenderableList[id].size();
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

unsigned long long IEECSRenderableSystem::getRenderableId(const int index) const
{
    if(!indexBoundCheck(index))
        return data.renderableIdList[0];

    return data.renderableIdList[index];
}

int IEECSRenderableSystem::getShownInstanceIndex(const int index) const
{
    if(!indexBoundCheck(index))
        return data.shownInstanceIndexList[0];

    return data.shownInstanceIndexList[index];
}

int IEECSRenderableSystem::getHiddenInstanceIndex(const int index) const
{
    if(!indexBoundCheck(index))
        return data.hiddenInstanceIndexList[0];

    return data.hiddenInstanceIndexList[index];
}

bool IEECSRenderableSystem::getIsRenderable(const int index) const
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

void IEECSRenderableSystem::setShownInstanceIndex(const int index, const int val)
{
    if(!indexBoundCheck(index))
        return;

    data.shownInstanceIndexList[index] = val;
}

void IEECSRenderableSystem::setHiddenInstanceIndex(const int index, const int val)
{
    if(!indexBoundCheck(index))
        return;

    data.hiddenInstanceIndexList[index] = val;
}

void IEECSRenderableSystem::setIsRenderable(const int index, const bool val)
{
    if(!indexBoundCheck(index))
        return;

    data.isRenderableList[index] = val;
}
