#include "IEInstanceData.h"

IEInstanceData::IEInstanceData() :
    shownEntityMap(), shownEntityList(),
    hiddenEntityMap(), hiddenEntityList()
{

}

IEInstanceData::IEInstanceData(const IEInstanceData& other) :
    shownEntityMap(other.shownEntityMap), shownEntityList(other.shownEntityList),
    hiddenEntityMap(other.hiddenEntityMap), hiddenEntityList(other.hiddenEntityList)
{

}

int IEInstanceData::addShown(const IEEntity& entity)
{
    if(doesExistShown(entity))
        return -1;

    return this->add(entity, shownEntityMap, shownEntityList);
}

// Returns the entity that was moved during the swap&pop
// and the index that entity was moved to.
std::tuple<IEEntity, int> IEInstanceData::removeShown(const IEEntity& entity)
{
    if(!doesExistShown(entity))
        return std::make_tuple(IEEntity(-1), -1);

    return this->remove(entity, shownEntityMap, shownEntityList);
}

int IEInstanceData::shownCount() const
{
    return shownEntityMap.size();
}

bool IEInstanceData::doesExistShown(const IEEntity& entity) const
{
    return shownEntityMap.contains(entity);
}

int IEInstanceData::lookUpShownIndex(const IEEntity& entity) const
{
    if(!doesExistShown(entity))
        return -1;

    return shownEntityMap[entity];
}

int IEInstanceData::addHidden(const IEEntity& entity)
{
    if(doesExistHidden(entity))
        return -1;

    return this->add(entity, hiddenEntityMap, hiddenEntityList);
}

// Returns the entity that was moved during the swap&pop
// and the index that entity was moved to.
std::tuple<IEEntity, int> IEInstanceData::removeHidden(const IEEntity& entity)
{
    if(!doesExistHidden(entity))
        return std::make_tuple(IEEntity(-1), -1);

    return this->remove(entity, hiddenEntityMap, hiddenEntityList);
}

int IEInstanceData::hiddenCount() const
{
    return hiddenEntityMap.size();
}

bool IEInstanceData::doesExistHidden(const IEEntity& entity) const
{
    return hiddenEntityMap.contains(entity);
}

int IEInstanceData::lookUpHiddenIndex(const IEEntity& entity) const
{
    if(!doesExistHidden(entity))
        return -1;

    return hiddenEntityMap[entity];
}

int IEInstanceData::add(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list)
{
    const int index = map.size();

    map[entity] = index;
    list.append(entity);

    return index;
}

std::tuple<IEEntity, int> IEInstanceData::remove(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list)
{
    const int indexToRemove = map[entity];

    const int lastIndex = map.size() - 1;
    const IEEntity lastEntity = list[lastIndex];

    list[indexToRemove] = lastEntity;
    list.removeLast();

    map[lastEntity] = indexToRemove;
    map.remove(entity);

    return std::make_tuple(lastEntity, indexToRemove);
}
