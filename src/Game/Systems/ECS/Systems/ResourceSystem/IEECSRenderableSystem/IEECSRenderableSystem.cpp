#include "IEECSRenderableSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IERenderableManager.h"
#include "IERenderable.h"

IEECSRenderableSystem::IEECSRenderableSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSRenderableSystem).hash_code(), parent),
    moreData(),
    shownEntityMap(), shownEntityList(),
    hiddenEntityMap(), hiddenEntityList(),
    renderableManager(nullptr)
{
    IEECSRenderableSystem::attach(IEEntity(-1));
}

IEECSRenderableSystem::~IEECSRenderableSystem()
{

}

int IEECSRenderableSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    moreData.shownInstanceIndex.append(-1);
    moreData.hiddenInstanceIndex.append(-1);
    moreData.tempVec2Data.append(QMap<QString, QVector2D>());
    moreData.tempVec3Data.append(QMap<QString, QVector3D>());
    moreData.tempVec4Data.append(QMap<QString, QVector4D>());
    moreData.tempMat4Data.append(QMap<QString, QMatrix4x4>());

    return IEECSResourceSystem::attach(entity);
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];
    const int lastIndex = entityMap.size() - 1;

    this->removeInstance(indexToRemove);

    moreData.shownInstanceIndex[indexToRemove] = moreData.shownInstanceIndex[lastIndex];
    moreData.hiddenInstanceIndex[indexToRemove] = moreData.hiddenInstanceIndex[lastIndex];
    moreData.tempVec2Data[indexToRemove] = moreData.tempVec2Data[lastIndex];
    moreData.tempVec3Data[indexToRemove] = moreData.tempVec3Data[lastIndex];
    moreData.tempVec4Data[indexToRemove] = moreData.tempVec4Data[lastIndex];
    moreData.tempMat4Data[indexToRemove] = moreData.tempMat4Data[lastIndex];

    moreData.shownInstanceIndex.removeLast();
    moreData.hiddenInstanceIndex.removeLast();
    moreData.tempVec2Data.removeLast();
    moreData.tempVec3Data.removeLast();
    moreData.tempVec4Data.removeLast();
    moreData.tempMat4Data.removeLast();

    return IEECSResourceSystem::detach(entity);
}

void IEECSRenderableSystem::startUp(const IEGame& game)
{
    renderableManager = game.getSystem<IEScene>()->getManager<IERenderableManager>();
}

void IEECSRenderableSystem::shutdown(const IEGame&)
{
    renderableManager = nullptr;
}

int IEECSRenderableSystem::addShown(const int index)
{
    if(doesExistShown(index))
        return -1;

    uint64_t id = data.resourceId[index];
    auto* renderable = renderableManager->value<IERenderable>(id);
    if(!renderable)
        return -1;

    const int instanceIndex = renderable->addShownInstance();
    moreData.shownInstanceIndex[index] = instanceIndex;

    IEEntity entity = data.entity[index];
    add(entity, shownEntityMap[id], shownEntityList[id]);

    return instanceIndex;
}

int IEECSRenderableSystem::addHidden(const int index)
{
    if(doesExistHidden(index))
        return -1;

    uint64_t id = data.resourceId[index];
    auto* renderable = renderableManager->value<IERenderable>(id);
    if(!renderable)
        return -1;

    const int instanceIndex = renderable->addHiddenInstance();
    moreData.hiddenInstanceIndex[index] = instanceIndex;

    IEEntity entity = data.entity[index];
    add(entity, hiddenEntityMap[id], hiddenEntityList[id]);

    cacheTempData(index);

    return instanceIndex;
}

void IEECSRenderableSystem::removeShown(const int index)
{
    if(!doesExistShown(index))
        return;

    uint64_t id = data.resourceId[index];
    auto* renderable = renderableManager->value<IERenderable>(id);
    if(!renderable)
        return;

    int instanceIndex = moreData.shownInstanceIndex[index];
    renderable->removeShownInstance(instanceIndex);

    IEEntity entityToRemove = data.entity[index];
    IEEntity movedEntity;
    int indexAt = -1;
    std::tie(movedEntity, indexAt) = this->remove(entityToRemove, shownEntityMap[id], shownEntityList[id]);
    if(indexAt > -1)
    {
        int movedEntityIndex = this->lookUpIndex(movedEntity);
        moreData.shownInstanceIndex[movedEntityIndex] = indexAt;
    }

    moreData.shownInstanceIndex[index] = -1;
}

void IEECSRenderableSystem::removeHidden(const int index)
{
    if(!doesExistHidden(index))
        return;

    uint64_t id = data.resourceId[index];
    auto* renderable = renderableManager->value<IERenderable>(id);
    if(!renderable)
        return;

    renderable->removeHiddenInstance();

    IEEntity entityToRemove = data.entity[index];
    IEEntity movedEntity;
    int indexAt = -1;
    std::tie(movedEntity, indexAt) = this->remove(entityToRemove, hiddenEntityMap[id], hiddenEntityList[id]);
    if(indexAt > -1)
    {
        int movedEntityIndex = this->lookUpIndex(movedEntity);
        moreData.hiddenInstanceIndex[movedEntityIndex] = indexAt;
    }

    moreData.hiddenInstanceIndex[index] = -1;

    transferTempData(index);
}

bool IEECSRenderableSystem::doesExistShown(const int index) const
{
    if(!indexBoundCheck(index))
        return false;

    uint64_t id = data.resourceId[index];
    if(!shownEntityMap.contains(id))
        return false;

    IEEntity entity = data.entity[index];
    return shownEntityMap[id].contains(entity);
}

bool IEECSRenderableSystem::doesExistHidden(const int index) const
{
    if(!indexBoundCheck(index))
        return false;

    uint64_t id = data.resourceId[index];
    if(!hiddenEntityMap.contains(id))
        return false;

    IEEntity entity = data.entity[index];
    return hiddenEntityMap[id].contains(entity);
}

void IEECSRenderableSystem::transferTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    uint64_t id = data.resourceId[index];
    auto* renderable = renderableManager->value<IERenderable>(id);
    if(!renderable)
        return;

    QMapIterator<QString, QVector2D> it1(moreData.tempVec2Data[index]);
    while(it1.hasNext()) { it1.next(); renderable->appendVec2InstanceValue(it1.key(), it1.value()); }

    QMapIterator<QString, QVector3D> it2(moreData.tempVec3Data[index]);
    while(it2.hasNext()) { it2.next(); renderable->appendVec3InstanceValue(it2.key(), it2.value()); }

    QMapIterator<QString, QVector4D> it3(moreData.tempVec4Data[index]);
    while(it3.hasNext()) { it3.next(); renderable->appendVec4InstanceValue(it3.key(), it3.value()); }

    QMapIterator<QString, QMatrix4x4> it4(moreData.tempMat4Data[index]);
    while(it4.hasNext()) { it4.next(); renderable->appendMat4InstanceValue(it4.key(), it4.value()); }

    clearTempData(index);
}


IERenderable* IEECSRenderableSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IERenderable>(index, renderableManager);
}

int IEECSRenderableSystem::getShownInstanceIndex(const int index) const
{
    if(!indexBoundCheck(index))
        return moreData.shownInstanceIndex[0];

    return moreData.shownInstanceIndex[index];
}

int IEECSRenderableSystem::getHiddenInstanceIndex(const int index) const
{
    if(!indexBoundCheck(index))
        return moreData.hiddenInstanceIndex[0];

    return moreData.hiddenInstanceIndex[index];
}

void IEECSRenderableSystem::setShownInstanceIndex(const int index, const int val)
{
    if(!indexBoundCheck(index))
        return;

    moreData.shownInstanceIndex[index] = val;
}

void IEECSRenderableSystem::setHiddenInstanceIndex(const int index, const int val)
{
    if(!indexBoundCheck(index))
        return;

    moreData.hiddenInstanceIndex[index] = val;
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

void IEECSRenderableSystem::removeInstance(const int index)
{
    if(!indexBoundCheck(index))
        return;

    this->removeShown(index);
    this->removeHidden(index);
    this->clearTempData(index);
}

void IEECSRenderableSystem::cacheTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    int instanceIndex = moreData.shownInstanceIndex[index];
    if(instanceIndex < 0)
        return;

    const uint64_t id = data.resourceId[index];
    auto renderable = renderableManager->value<IERenderable>(id);
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

    moreData.tempVec2Data[index] = vec2Data;
    moreData.tempVec3Data[index] = vec3Data;
    moreData.tempVec4Data[index] = vec4Data;
    moreData.tempMat4Data[index] = mat4Data;
}

void IEECSRenderableSystem::clearTempData(const int index)
{
    if(!indexBoundCheck(index))
        return;

    moreData.tempVec2Data[index].clear();
    moreData.tempVec3Data[index].clear();
    moreData.tempVec4Data[index].clear();
    moreData.tempMat4Data[index].clear();
}

QDataStream& IEECSRenderableSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    IEECSResourceSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSRenderableSystem&>(obj);

    out << system.moreData
        << system.shownEntityMap << system.shownEntityList
        << system.hiddenEntityMap << system.hiddenEntityList;

    return out;
}

QDataStream& IEECSRenderableSystem::deserialize(QDataStream& in, Serializable& obj)
{
    IEECSResourceSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSRenderableSystem&>(obj);

    in >> system.moreData
       >> system.shownEntityMap >> system.shownEntityList
       >> system.hiddenEntityMap >> system.hiddenEntityList;

    return in;
}
