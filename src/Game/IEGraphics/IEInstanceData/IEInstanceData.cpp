#include "IEInstanceData.h"

IEInstanceData::IEInstanceData() :
    entityMap(),
    entityList()
{

}

IEInstanceData::IEInstanceData(const IEInstanceData& other) :
    entityMap(other.entityMap),
    entityList(other.entityList)
{

}

int IEInstanceData::add(const IEEntity& entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;
    entityList.append(entity);

    return index;
}

// Returns the entity that was moved during the swap&pop
// and the index that was removed.
std::tuple<IEEntity, int> IEInstanceData::remove(const IEEntity& entity)
{
    if(!doesExist(entity))
        return std::make_tuple(IEEntity(-1), -1);

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = entityList[lastIndex];

    entityList[indexToRemove] = lastEntity;
    entityList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return std::make_tuple(lastEntity, indexToRemove);
}

int IEInstanceData::count() const
{
    return entityMap.size();
}

bool IEInstanceData::doesExist(const IEEntity& entity) const
{
    return entityMap.contains(entity);
}

int IEInstanceData::lookUpIndex(const IEEntity& entity) const
{
    if(!doesExist(entity))
        return -1;

    return entityMap[entity];
}
