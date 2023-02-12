#include "IEECSSystem.h"

IEECSSystem::IEECSSystem() :
    entityMap()
{

}

IEECSSystem::~IEECSSystem()
{

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
