#include "IEECSRenderableSystem.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "ECSOnUpdateEvent.h"

IEECSRenderableSystem::IEECSRenderableSystem() :
    IEECSSystem(),
    data(),
    renderableManager(nullptr)
{
    IEECSRenderableSystem::attach(IEEntity(-1));
}

IEECSRenderableSystem::~IEECSRenderableSystem()
{
    renderableManager = nullptr;
}

void IEECSRenderableSystem::startup(const GameStartEvent& event)
{
    renderableManager = event.getScene()->getRenderableManager();
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
    data.tempVec2Data.append(QMap<QString, QVector2D>());

    return index;
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    this->removeInstanceFromRenderable(data.renderableIdList[indexToRemove], entity);

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.renderableIdList[indexToRemove] = data.renderableIdList[lastIndex];
    data.shownInstanceIndexList[indexToRemove] = data.shownInstanceIndexList[lastIndex];
    data.hiddenInstanceIndexList[indexToRemove] = data.hiddenInstanceIndexList[lastIndex];
    data.tempVec2Data[indexToRemove] = data.tempVec2Data[lastIndex];

    data.entityList.removeLast();
    data.renderableIdList.removeLast();
    data.shownInstanceIndexList.removeLast();
    data.hiddenInstanceIndexList.removeLast();
    data.tempVec2Data.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSRenderableSystem::onUpdateFrame(ECSOnUpdateEvent*)
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
            this->setShownInstanceIndex(i, -1);
            this->setHiddenInstanceIndex(i, -1);
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

QMap<QString, QVector2D> IEECSRenderableSystem::getTempVec2Data(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tempVec2Data[0];

    return data.tempVec2Data[index];
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

void IEECSRenderableSystem::setTempVec2Data(const int index, const QMap<QString, QVector2D>& val)
{
    if(!indexBoundCheck(index))
        return;

    data.tempVec2Data[index] = val;
}

void IEECSRenderableSystem::removeInstanceFromRenderable(const unsigned long long id, const IEEntity& entity)
{
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    // Remove shown instance
    IEEntity movedEntity;
    int indexAt = -1;
    std::tie(movedEntity, indexAt) = renderable->removeShownInstance(entity);
    if(indexAt > -1)
    {
        int movedEntityIndex = this->lookUpIndex(movedEntity);
        data.shownInstanceIndexList[movedEntityIndex] = indexAt;
    }

    // Remove hidden instance
    std::tie(movedEntity, indexAt) = renderable->removeHiddenInstance(entity);
    if(indexAt > -1)
    {

        int movedEntityIndex = this->lookUpIndex(movedEntity);
        data.hiddenInstanceIndexList[movedEntityIndex] = indexAt;
    }
}
