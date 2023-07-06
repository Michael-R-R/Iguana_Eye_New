#include "IEECSResourceSystem.h"

IEECSResourceSystem::IEECSResourceSystem(size_t id, QObject* parent) :
    IEECSSystem(id, parent),
    data(), idIndexPair()
{

}

IEECSResourceSystem::~IEECSResourceSystem()
{

}

int IEECSResourceSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.resourceId.append(0);

    return index;
}

bool IEECSResourceSystem::detach(const IEEntity entity)
{
    if (!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];
    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entity[lastIndex];

    // Remove indexToRemove from IdIndexPair
    uint64_t toRemoveId = data.resourceId[indexToRemove];
    if (doesResourceIdExist(toRemoveId))
        idIndexPair[toRemoveId].remove(indexToRemove);

    // Update lastIndex in idIndexPair
    uint64_t toUpdateId = data.resourceId[lastIndex];
    if (doesResourceIdExist(toUpdateId))
    {
        idIndexPair[toUpdateId].remove(lastIndex);
        idIndexPair[toUpdateId].insert(indexToRemove);
    }

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.resourceId[indexToRemove] = data.resourceId[lastIndex];

    data.entity.removeLast();
    data.entity.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

QSet<int> IEECSResourceSystem::massReplaceResourceId(const uint64_t oldId, const uint64_t newId)
{
    if (!doesResourceIdExist(oldId))
        return QSet<int>();

    if (doesResourceIdExist(newId))
        return QSet<int>();

    auto tempHashSet = idIndexPair[oldId];
    idIndexPair.remove(oldId);
    idIndexPair.insert(newId, tempHashSet);

    for (int i = 1; i < tempHashSet.size(); i++)
    {
        data.resourceId[i] = newId;
    }

    return tempHashSet;
}

QSet<int> IEECSResourceSystem::massPurgeResourceId(uint64_t id)
{
    if (!doesResourceIdExist(id))
        return QSet<int>();

    auto tempHashSet = idIndexPair[id];
    idIndexPair.remove(id);

    for (int i = 1; i < tempHashSet.size(); i++)
    {
        data.resourceId[i] = 0;
    }

    return tempHashSet;
}

bool IEECSResourceSystem::doesResourceIdExist(const uint64_t id)
{
    return idIndexPair.contains(id);
}

uint64_t IEECSResourceSystem::getResourceId(const int index)
{
    if(!indexBoundCheck(index))
        return 0;

    return data.resourceId[index];
}

void IEECSResourceSystem::setResourceId(const int index, uint64_t val)
{
    if(!indexBoundCheck(index))
        return;

    uint64_t oldId = data.resourceId[index];
    if (doesResourceIdExist(oldId))
        idIndexPair[oldId].remove(index);

    if (doesResourceIdExist(val))
        idIndexPair[val].insert(index);
    else
        idIndexPair.insert(val, QSet<int> { index });

    data.resourceId[index] = val;
}

QDataStream& IEECSResourceSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEECSSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSResourceSystem&>(obj);

    out << system.data << system.idIndexPair;

    return out;
}

QDataStream& IEECSResourceSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    IEECSSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSResourceSystem&>(obj);

    in >> system.data >> system.idIndexPair;

    return in;
}
