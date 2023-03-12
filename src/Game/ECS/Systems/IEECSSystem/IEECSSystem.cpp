#include "IEECSSystem.h"

IEECSSystem::IEECSSystem() :
    entityMap()
{

}

IEECSSystem::~IEECSSystem()
{

}

QDataStream& IEECSSystem::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEECSSystem::deserialize(QDataStream& in, Serializable&)
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
    return (index > 0 && index < entityMap.size());
}
