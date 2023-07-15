#include "IEECSRenderableSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IERenderableManager.h"
#include "IEInstRenderable.h"
#include "IEEntity.h"

IEECSRenderableSystem::IEECSRenderableSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSRenderableSystem).hash_code(), parent),
    moreData(),
    mappedShownIndices(),
    mappedHiddenIndices(),
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

    moreData.shownIndex.append(-1);
    moreData.hiddenIndex.append(-1);

    return IEECSResourceSystem::attach(entity);
}

bool IEECSRenderableSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];
    const int lastIndex = entityMap.size() - 1;

    removeInstance(indexToRemove);

    moreData.shownIndex[indexToRemove] = moreData.shownIndex[lastIndex];
    moreData.hiddenIndex[indexToRemove] = moreData.hiddenIndex[lastIndex];

    moreData.shownIndex.removeLast();
    moreData.hiddenIndex.removeLast();

    return IEECSResourceSystem::detach(entity);
}

void IEECSRenderableSystem::startUp(const IEGame& game)
{
    renderableManager = game.getSystem<IEScene>()->getSystem<IERenderableManager>();
}

void IEECSRenderableSystem::shutdown(const IEGame&)
{
    renderableManager = nullptr;
}

IEInstRenderable* IEECSRenderableSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IEInstRenderable>(index, renderableManager);
}

int IEECSRenderableSystem::getShownIndex(const int index) const
{
    if (!indexBoundCheck(index))
        return -1;

    return moreData.shownIndex[index];
}

int IEECSRenderableSystem::getHiddenIndex(const int index) const
{
    if (!indexBoundCheck(index))
        return -1;

    return moreData.hiddenIndex[index];
}

int IEECSRenderableSystem::showInstance(const int index)
{
    if(!indexBoundCheck(index))
        return -1;

    if(moreData.shownIndex[index] > -1)
        return moreData.shownIndex[index];

    if(moreData.hiddenIndex[index] > -1)
        return addShownFromHidden(index);

    return addShown(index);
}

int IEECSRenderableSystem::hideInstance(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }

    if(moreData.shownIndex[index] < 0)
        return -1;

    const uint64_t rID = renderable->getID();
    const int lastShownIndex = renderable->shownCount() - 1;
    const int currShownIndex = moreData.shownIndex[index];
    const int currHiddenIndex = renderable->addHiddenFromShown(currShownIndex);
    if(currHiddenIndex < 0)
        return -1;

    removeMappedIndex(rID, currShownIndex, mappedShownIndices);
    addMappedIndex(rID, currHiddenIndex, data.entity[index], mappedHiddenIndices);

    moreData.shownIndex[index] = -1;
    moreData.hiddenIndex[index] = currHiddenIndex;

    updateSwappedIndex(rID, lastShownIndex, currShownIndex, moreData.shownIndex, mappedShownIndices);

    return currHiddenIndex;
}

void IEECSRenderableSystem::removeInstance(const int index)
{
    removeShown(index);
    removeHidden(index);
}

int IEECSRenderableSystem::addShown(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }

    const uint64_t rID = renderable->getID();
    const int shownIndex = renderable->addShown();

    addMappedIndex(rID, shownIndex, data.entity[index], mappedShownIndices);

    moreData.shownIndex[index] = shownIndex;

    return shownIndex;
}

int IEECSRenderableSystem::addShownFromHidden(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }

    const uint64_t rID = renderable->getID();
    const int lastHiddenIndex = renderable->hiddenCount() - 1;
    const int currHiddenIndex = moreData.hiddenIndex[index];
    const int currShownIndex = renderable->addShownFromHidden(currHiddenIndex);
    if(currShownIndex < 0)
        return -1;

    removeMappedIndex(rID, currHiddenIndex, mappedHiddenIndices);
    addMappedIndex(rID, currShownIndex, data.entity[index], mappedShownIndices);

    moreData.shownIndex[index] = currShownIndex;
    moreData.hiddenIndex[index] = -1;

    updateSwappedIndex(rID, lastHiddenIndex, currHiddenIndex, moreData.hiddenIndex, mappedHiddenIndices);

    return currShownIndex;
}

void IEECSRenderableSystem::removeShown(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return; }

    const uint64_t rID = renderable->getID();
    const int lastShownIndex = renderable->shownCount() - 1;
    const int currShownIndex = moreData.shownIndex[index];
    if(!renderable->removeShown(currShownIndex))
        return;

    removeMappedIndex(rID, currShownIndex, mappedShownIndices);
    moreData.shownIndex[index] = -1;

    updateSwappedIndex(rID, lastShownIndex, currShownIndex, moreData.shownIndex, mappedShownIndices);
}

void IEECSRenderableSystem::removeHidden(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return; }

    const uint64_t rID = renderable->getID();
    const int lastHiddenIndex = renderable->hiddenCount() - 1;
    const int currHiddenIndex = moreData.hiddenIndex[index];
    if (!renderable->removeHidden(currHiddenIndex))
        return;

    removeMappedIndex(rID, currHiddenIndex, mappedHiddenIndices);

    moreData.hiddenIndex[index] = -1;

    updateSwappedIndex(rID, lastHiddenIndex, currHiddenIndex, moreData.hiddenIndex, mappedHiddenIndices);
}

bool IEECSRenderableSystem::doesMappedIdExist(const uint64_t id,
                                              const QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    return map.contains(id);
}

bool IEECSRenderableSystem::doesMappedIndexExist(const uint64_t id, const int index, const QHash<uint64_t, QHash<int, IEEntity> >& map)
{
    if(!doesMappedIdExist(id, map))
        return false;

    return map[id].contains(index);
}

void IEECSRenderableSystem::addMappedIndex(const uint64_t id,
                                           const int index,
                                           const IEEntity entity,
                                           QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIdExist(id, map))
        map.insert(id, QHash<int, IEEntity>{});

    map[id].insert(index, entity);
}

void IEECSRenderableSystem::removeMappedIndex(const uint64_t id,
                                              const int index,
                                              QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIndexExist(id, index, map))
        return;

    map[id].remove(index);

    if(map[id].size() <= 0)
        map.remove(id);
}

void IEECSRenderableSystem::replaceMappedIndex(const uint64_t id,
                                               const int oldIndex,
                                               const int newIndex,
                                               QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIndexExist(id, oldIndex, map))
        return;

    if(doesMappedIndexExist(id, newIndex, map))
        return;

    const IEEntity temp = map[id][oldIndex];
    map[id].remove(oldIndex);
    map[id].insert(newIndex, temp);
}

void IEECSRenderableSystem::updateSwappedIndex(const uint64_t id,
                                               const int lastIndex,
                                               const int newIndex,
                                               QVector<int>& list,
                                               QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIndexExist(id, lastIndex, map))
        return;

    const IEEntity lastEntity = map[id][lastIndex];
    const int lookupIndex = lookUpIndex(lastEntity);
    list[lookupIndex] = newIndex;
    replaceMappedIndex(id, lastIndex, newIndex, map);
}

QDataStream& IEECSRenderableSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEECSResourceSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSRenderableSystem&>(obj);

    out << system.moreData;

    return out;
}

QDataStream& IEECSRenderableSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    IEECSResourceSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSRenderableSystem&>(obj);

    in >> system.moreData;

    return in;
}
