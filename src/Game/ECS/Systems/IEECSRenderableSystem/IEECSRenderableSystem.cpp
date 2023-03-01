#include "IEECSRenderableSystem.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "ECSOnUpdateEvent.h"

IEECSRenderableSystem::IEECSRenderableSystem() :
    IEECSSystem(),
    data(),
    shownEntityMap(), shownEntityList(),
    hiddenEntityMap(), hiddenEntityList(),
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
    data.tempVec3Data.append(QMap<QString, QVector3D>());
    data.tempVec4Data.append(QMap<QString, QVector4D>());
    data.tempMat4Data.append(QMap<QString, QMatrix4x4>());

    return index;
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    this->removeInstanceFromRenderable(indexToRemove);

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.renderableIdList[indexToRemove] = data.renderableIdList[lastIndex];
    data.shownInstanceIndexList[indexToRemove] = data.shownInstanceIndexList[lastIndex];
    data.hiddenInstanceIndexList[indexToRemove] = data.hiddenInstanceIndexList[lastIndex];
    data.tempVec2Data[indexToRemove] = data.tempVec2Data[lastIndex];
    data.tempVec3Data[indexToRemove] = data.tempVec3Data[lastIndex];
    data.tempVec4Data[indexToRemove] = data.tempVec4Data[lastIndex];
    data.tempMat4Data[indexToRemove] = data.tempMat4Data[lastIndex];

    data.entityList.removeLast();
    data.renderableIdList.removeLast();
    data.shownInstanceIndexList.removeLast();
    data.hiddenInstanceIndexList.removeLast();
    data.tempVec2Data.removeLast();
    data.tempVec3Data.removeLast();
    data.tempVec4Data.removeLast();
    data.tempMat4Data.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSRenderableSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

void IEECSRenderableSystem::addShown(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(doesExistShown(index))
        return;

    unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    const int instanceIndex = renderable->addShownInstance();
    data.shownInstanceIndexList[index] = instanceIndex;

    IEEntity entity = data.entityList[index];
    add(entity, shownEntityMap[id], shownEntityList[id]);
}

void IEECSRenderableSystem::addHidden(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(doesExistHidden(index))
        return;

    unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    const int instanceIndex = renderable->addHiddenInstance();
    data.hiddenInstanceIndexList[index] = instanceIndex;

    IEEntity entity = data.entityList[index];
    add(entity, hiddenEntityMap[id], hiddenEntityList[id]);

    cacheTempData(index);
}

void IEECSRenderableSystem::removeShown(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!doesExistShown(index))
        return;

    unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    int instanceIndex = data.shownInstanceIndexList[index];
    renderable->removeShownInstance(instanceIndex);

    IEEntity entityToRemove = data.entityList[index];
    IEEntity movedEntity;
    int indexAt = -1;
    std::tie(movedEntity, indexAt) = this->remove(entityToRemove, shownEntityMap[id], shownEntityList[id]);
    if(indexAt > -1)
    {
        int movedEntityIndex = this->lookUpIndex(movedEntity);
        data.shownInstanceIndexList[movedEntityIndex] = indexAt;
    }

    data.shownInstanceIndexList[index] = -1;
}

void IEECSRenderableSystem::removeHidden(const int index)
{
    if(!indexBoundCheck(index))
        return;

    if(!doesExistHidden(index))
        return;

    unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    renderable->removeHiddenInstance();

    IEEntity entityToRemove = data.entityList[index];
    IEEntity movedEntity;
    int indexAt = -1;
    std::tie(movedEntity, indexAt) = this->remove(entityToRemove, hiddenEntityMap[id], hiddenEntityList[id]);
    if(indexAt > -1)
    {
        int movedEntityIndex = this->lookUpIndex(movedEntity);
        data.hiddenInstanceIndexList[movedEntityIndex] = indexAt;
    }

    data.hiddenInstanceIndexList[index] = -1;
}

bool IEECSRenderableSystem::doesExistShown(const int index) const
{
    if(!indexBoundCheck(index))
        return false;

    unsigned long long id = data.renderableIdList[index];
    if(!shownEntityMap.contains(id))
        return false;

    IEEntity entity = data.entityList[index];
    return shownEntityMap[id].contains(entity);
}

bool IEECSRenderableSystem::doesExistHidden(const int index) const
{
    if(!indexBoundCheck(index))
        return false;

    unsigned long long id = data.renderableIdList[index];
    if(!hiddenEntityMap.contains(id))
        return false;

    IEEntity entity = data.entityList[index];
    return hiddenEntityMap[id].contains(entity);
}

void IEECSRenderableSystem::transferTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    QMapIterator<QString, QVector2D> it1(data.tempVec2Data[index]);
    while(it1.hasNext()) { it1.next(); renderable->appendVec2InstanceValue(it1.key(), it1.value()); }

    QMapIterator<QString, QVector3D> it2(data.tempVec3Data[index]);
    while(it2.hasNext()) { it2.next(); renderable->appendVec3InstanceValue(it2.key(), it2.value()); }

    QMapIterator<QString, QVector4D> it3(data.tempVec4Data[index]);
    while(it3.hasNext()) { it3.next(); renderable->appendVec4InstanceValue(it3.key(), it3.value()); }

    QMapIterator<QString, QMatrix4x4> it4(data.tempMat4Data[index]);
    while(it4.hasNext()) { it4.next(); renderable->appendMat4InstanceValue(it4.key(), it4.value()); }

    clearTempData(index);
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

const QMap<QString, QVector2D>& IEECSRenderableSystem::getTempVec2Data(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tempVec2Data[0];

    return data.tempVec2Data[index];
}

const QMap<QString, QVector3D>& IEECSRenderableSystem::getTempVec3Data(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tempVec3Data[0];

    return data.tempVec3Data[index];
}

const QMap<QString, QVector4D>& IEECSRenderableSystem::getTempVec4Data(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tempVec4Data[0];

    return data.tempVec4Data[index];
}

const QMap<QString, QMatrix4x4>& IEECSRenderableSystem::getTempMat4Data(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tempMat4Data[0];

    return data.tempMat4Data[index];
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

void IEECSRenderableSystem::setTempVec3Data(const int index, const QMap<QString, QVector3D>& val)
{
    if(!indexBoundCheck(index))
        return;

    data.tempVec3Data[index] = val;
}

void IEECSRenderableSystem::setTempVec4Data(const int index, const QMap<QString, QVector4D>& val)
{
    if(!indexBoundCheck(index))
        return;

    data.tempVec4Data[index] = val;
}

void IEECSRenderableSystem::setTempMat4Data(const int index, const QMap<QString, QMatrix4x4>& val)
{
    if(!indexBoundCheck(index))
        return;

    data.tempMat4Data[index] = val;
}

int IEECSRenderableSystem::add(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list)
{
    const int index = map.size();

    map[entity] = index;
    list.append(entity);

    return index;
}

std::tuple<IEEntity, int> IEECSRenderableSystem::remove(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list)
{
    // Method returns the entity that was moved during the swap&pop
    // and the index that entity was moved to.

    const int indexToRemove = map[entity];

    const int lastIndex = map.size() - 1;
    const IEEntity lastEntity = list[lastIndex];

    list[indexToRemove] = lastEntity;
    list.removeLast();

    map[lastEntity] = indexToRemove;
    map.remove(entity);

    return std::make_tuple(lastEntity, indexToRemove);
}

void IEECSRenderableSystem::removeInstanceFromRenderable(const int index)
{
    if(!indexBoundCheck(index))
        return;

    const unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    // Remove shown instance
    this->removeShown(index);

    // Remove hidden instance
    this->removeHidden(index);

    this->clearTempData(index);
}

void IEECSRenderableSystem::cacheTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    int instanceIndex = data.shownInstanceIndexList[index];
    if(instanceIndex < 0)
        return;

    const unsigned long long id = data.renderableIdList[index];
    auto renderable = renderableManager->getValue(id);
    if(!renderable)
        return;

    QMap<QString, QVector2D> vec2Data;
    QMap<QString, QVector3D> vec3Data;
    QMap<QString, QVector4D> vec4Data;
    QMap<QString, QMatrix4x4> mat4Data;
    renderable->fetchBufferDataAtIndex(instanceIndex,
                                       vec2Data,
                                       vec3Data,
                                       vec4Data,
                                       mat4Data);

    data.tempVec2Data[index] = vec2Data;
    data.tempVec3Data[index] = vec3Data;
    data.tempVec4Data[index] = vec4Data;
    data.tempMat4Data[index] = mat4Data;
}

void IEECSRenderableSystem::clearTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.tempVec2Data[index].clear();
    data.tempVec3Data[index].clear();
    data.tempVec4Data[index].clear();
    data.tempMat4Data[index].clear();
}
