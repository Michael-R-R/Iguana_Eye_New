#include "IEECSSystem.h"

IEECSSystem::IEECSSystem() :
    entityMap()
{

}

IEECSSystem::~IEECSSystem()
{

}

bool IEECSSystem::doesExist(const IEEntity& key)
{
    return entityMap.contains(key);
}

int IEECSSystem::lookUpIndex(const IEEntity& key)
{
    if(!doesExist(key))
        return -1;

    return entityMap[key];
}

bool IEECSSystem::indexBoundCheck(const int index)
{
    return (index > -1 && index < entityMap.size());
}
