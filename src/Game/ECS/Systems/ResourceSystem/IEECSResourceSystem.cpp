#include "IEECSResourceSystem.h"

IEECSResourceSystem::IEECSResourceSystem(QObject* parent) :
    IEECSSystem(parent),
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
    unsigned long long toRemoveId = data.resourceId[indexToRemove];
    if (doesResourceIdExist(toRemoveId))
        idIndexPair[toRemoveId].remove(indexToRemove);

    // Update lastIndex in idIndexPair
    unsigned long long toUpdateId = data.resourceId[lastIndex];
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

QSet<int> IEECSResourceSystem::massReplaceResourceId(const unsigned long long oldId, const unsigned long long newId)
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

QSet<int> IEECSResourceSystem::massPurgeResourceId(unsigned long long id)
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

bool IEECSResourceSystem::doesResourceIdExist(const unsigned long long id)
{
    return idIndexPair.contains(id);
}

unsigned long long IEECSResourceSystem::getResourceId(const int index)
{
    if(!indexBoundCheck(index))
        return 0;

    return data.resourceId[index];
}

void IEECSResourceSystem::setResourceId(const int index, unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    unsigned long long oldId = data.resourceId[index];
    if (doesResourceIdExist(oldId))
        idIndexPair[oldId].remove(index);

    if (doesResourceIdExist(val))
        idIndexPair[val].insert(index);
    else
        idIndexPair.insert(val, QSet<int> { index });

    data.resourceId[index] = val;
}

QDataStream& IEECSResourceSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    IEECSSystem::serialize(out, obj);

    const auto& system = static_cast<const IEECSResourceSystem&>(obj);

    out << system.data << system.idIndexPair;

    return out;
}

QDataStream& IEECSResourceSystem::deserialize(QDataStream& in, Serializable& obj)
{
    IEECSSystem::deserialize(in, obj);

    auto& system = static_cast<IEECSResourceSystem&>(obj);

    in >> system.data >> system.idIndexPair;

    return in;
}
