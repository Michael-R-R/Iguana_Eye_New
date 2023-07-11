#include "IEECSRenderableSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IERenderableManager.h"
#include "IEInstRenderable.h"
#include "IEEntity.h"

IEECSRenderableSystem::IEECSRenderableSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSRenderableSystem).hash_code(), parent),
    moreData(),
    ShownMappedIndices(),
    HiddenMappedIndices(),
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
    renderableManager = game.getSystem<IEScene>()->getManager<IERenderableManager>();
}

void IEECSRenderableSystem::shutdown(const IEGame&)
{
    renderableManager = nullptr;
}

QSet<int> IEECSRenderableSystem::massReplaceResourceId(const uint64_t oldId, const uint64_t newId)
{
    if(doesMappedIdExist(oldId, ShownMappedIndices))
    {
        if(!doesMappedIdExist(newId, ShownMappedIndices))
        {
            auto& tempHash = ShownMappedIndices[oldId];
            ShownMappedIndices.remove(oldId);
            ShownMappedIndices.insert(newId, tempHash);
        }
    }

    if(doesMappedIdExist(oldId, HiddenMappedIndices))
    {
        if(!doesMappedIdExist(newId, HiddenMappedIndices))
        {
            auto& tempHash = HiddenMappedIndices[oldId];
            HiddenMappedIndices.remove(oldId);
            HiddenMappedIndices.insert(newId, tempHash);
        }
    }

    return IEECSResourceSystem::massReplaceResourceId(oldId, newId);
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

int IEECSRenderableSystem::addShown(const int index)
{
    if (!indexBoundCheck(index))
        return -1;

    // Already exist, return current shown index
    if(moreData.shownIndex[index] > -1) { return moreData.shownIndex[index]; }
    // Has hidden instance
    else if(moreData.hiddenIndex[index] > -1) { return hiddenToShown(index); }
    // Create a new instance
    else { createInstance(index); }
}

bool IEECSRenderableSystem::removeShown(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return false; }

    const uint64_t id = renderable->getId();
    const int lastShownIndex = renderable->getShownCount() - 1;
    const int currShownIndex = moreData.shownIndex[index];

    foreach (auto* c, renderable->getChildren())
    {
        foreach(auto* r, c->getRenderables())
        {
            auto* temp = static_cast<IEInstRenderable*>(r);
            if(!temp->removeShown(currShownIndex))
                return false;
        }
    }

    removeMappedIndex(id, currShownIndex, ShownMappedIndices);
    moreData.shownIndex[index] = -1;

    updateSwappedIndex(id, lastShownIndex, currShownIndex, moreData.shownIndex, ShownMappedIndices);

    return true;
}

int IEECSRenderableSystem::addHidden(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }
    if(moreData.shownIndex[index] < 0) { return -1; }

    const uint64_t id = renderable->getId();
    const int lastShownIndex = renderable->getShownCount() - 1;
    const int currShownIndex = moreData.shownIndex[index];
    int currHiddenIndex = -1;

    foreach (auto* c, renderable->getChildren())
    {
        foreach(auto* r, c->getRenderables())
        {
            auto* temp = static_cast<IEInstRenderable*>(r);
            currHiddenIndex = temp->addHidden(currShownIndex);
            if(currHiddenIndex < 0)
                return -1;
        }
    }

    removeMappedIndex(id, currShownIndex, ShownMappedIndices);
    addMappedIndex(id, currHiddenIndex, data.entity[index], HiddenMappedIndices);
    moreData.shownIndex[index] = -1;
    moreData.hiddenIndex[index] = currHiddenIndex;

    updateSwappedIndex(id, lastShownIndex, currShownIndex, moreData.shownIndex, ShownMappedIndices);

    return currHiddenIndex;
}

bool IEECSRenderableSystem::removeHidden(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return false; }

    const uint64_t id = renderable->getId();
    const int lastHiddenIndex = renderable->getHiddenCount() - 1;
    const int currHiddenIndex = moreData.hiddenIndex[index];

    foreach (auto* c, renderable->getChildren())
    {
        foreach(auto* r, c->getRenderables())
        {
            auto* temp = static_cast<IEInstRenderable*>(r);
            if(!temp->removeHidden(currHiddenIndex))
                return false;
        }
    }

    removeMappedIndex(id, currHiddenIndex, HiddenMappedIndices);
    moreData.hiddenIndex[index] = -1;

    updateSwappedIndex(id, lastHiddenIndex, currHiddenIndex, moreData.hiddenIndex, HiddenMappedIndices);

    return true;
}

void IEECSRenderableSystem::removeInstance(const int index)
{
    removeShown(index);
    removeHidden(index);
}

int IEECSRenderableSystem::createInstance(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }

    const uint64_t id = renderable->getId();
    int shownIndex = -1;

    foreach (auto* c, renderable->getChildren())
    {
        foreach(auto* r, c->getRenderables())
        {
            auto* temp = static_cast<IEInstRenderable*>(r);
            shownIndex = temp->addShown();
        }
    }

    addMappedIndex(id, shownIndex, data.entity[index], ShownMappedIndices);
    moreData.shownIndex[index] = shownIndex;

    return shownIndex;
}

int IEECSRenderableSystem::hiddenToShown(const int index)
{
    auto* renderable = getAttachedResource(index);
    if(!renderable) { return -1; }

    const uint64_t id = renderable->getId();
    const int lastHiddenIndex = renderable->getHiddenCount() - 1;
    const int currHiddenIndex = moreData.hiddenIndex[index];
    int currShownIndex = -1;

    foreach (auto* c, renderable->getChildren())
    {
        foreach(auto* r, c->getRenderables())
        {
            auto* temp = static_cast<IEInstRenderable*>(r);
            currShownIndex = temp->addShown(currHiddenIndex);
            if(currShownIndex < 0)
                return -1;
        }
    }

    removeMappedIndex(id, currHiddenIndex, HiddenMappedIndices);
    addMappedIndex(id, currShownIndex, data.entity[index], ShownMappedIndices);
    moreData.hiddenIndex[index] = -1;
    moreData.shownIndex[index] = currShownIndex;

    updateSwappedIndex(id, lastHiddenIndex, currHiddenIndex, moreData.hiddenIndex, HiddenMappedIndices);

    return currShownIndex;
}

bool IEECSRenderableSystem::doesMappedIdExist(const uint64_t id, const QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    return map.contains(id);
}

bool IEECSRenderableSystem::doesMappedIndexExist(const uint64_t id, const int index, const QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIdExist(id, map))
        return false;

    return map[id].contains(index);
}

void IEECSRenderableSystem::updateSwappedIndex(const uint64_t id, const int lastIndex, const int newIndex, QVector<int>& list, QHash<uint64_t, QHash<int, IEEntity> >& map)
{
    if(!doesMappedIndexExist(id, lastIndex, map)) { return; }

    IEEntity lastEntity = map[id][lastIndex];
    const int lookupIndex = lookUpIndex(lastEntity);
    list[lookupIndex] = newIndex;

    replaceMappedIndex(id, lastIndex, newIndex, map);
}

void IEECSRenderableSystem::addMappedIndex(const uint64_t id, const int index, const IEEntity& entity, QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIdExist(id, map))
        map.insert(id, QHash<int, IEEntity>{});

    map[id].insert(index, entity);
}

void IEECSRenderableSystem::replaceMappedIndex(const uint64_t id, const int oldIndex, const int newIndex, QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIndexExist(id, oldIndex, map)) { return; }
    if(!doesMappedIndexExist(id, newIndex, map)) { return; }

    auto tempEntity = map[id][oldIndex];
    map[id].remove(oldIndex);
    map[id].insert(newIndex, tempEntity);
}

void IEECSRenderableSystem::removeMappedIndex(const uint64_t id, const int index, QHash<uint64_t, QHash<int, IEEntity>>& map)
{
    if(!doesMappedIndexExist(id, index, map)) { return; }

    map[id].remove(index);

    if(map[id].size() <= 0) { map.remove(id); }
}

QDataStream& IEECSRenderableSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEECSResourceSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSRenderableSystem&>(obj);

    out << system.moreData << system.ShownMappedIndices << system.HiddenMappedIndices;

    return out;
}

QDataStream& IEECSRenderableSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    IEECSResourceSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSRenderableSystem&>(obj);

    in >> system.moreData >> system.ShownMappedIndices >> system.HiddenMappedIndices;

    return in;
}
