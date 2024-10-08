#include "IEECSSystem.h"

IEECSSystem::IEECSSystem(size_t _id, QObject* parent) :
    IEObject(parent),
    id(_id), entityMap()
{

}

IEECSSystem::~IEECSSystem()
{

}

QDataStream& IEECSSystem::serialize(QDataStream& out, const IESerializable&) const
{
    return out;
}

QDataStream& IEECSSystem::deserialize(QDataStream& in, IESerializable&)
{
    return in;
}

bool IEECSSystem::doesExist(const IEEntity& key) const
{
    return entityMap.contains(key);
}

int IEECSSystem::lookUpIndex(const IEEntity& key) const
{
    if(!doesExist(key))
        return -1;

    return entityMap[key];
}

bool IEECSSystem::indexBoundCheck(const int index) const
{
    // Valid indexing starts at: 1
    return (index > 0 && index < entityMap.size());
}
