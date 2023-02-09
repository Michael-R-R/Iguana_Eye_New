#include "IEEntityManager.h"

IEEntityManager::IEEntityManager() :
    entityMap(),
    freeIdStack(),
    nextId(0)
{

}

IEEntityManager::~IEEntityManager()
{

}

IEEntity IEEntityManager::create()
{
    IEEntity entity = IEEntity(-1);

    if(freeIdStack.size() > 0)
    {
        entity = IEEntity(freeIdStack.pop());
    }
    else
    {
        entity = IEEntity(++nextId);
        while(doesExist(entity))
        {
            entity = IEEntity(++nextId);
        }
    }

    entityMap[entity] = 0;

    return entity;
}

bool IEEntityManager::remove(const IEEntity key)
{
    if(!doesExist(key))
        return false;

    entityMap.remove(key);

    return true;
}

bool IEEntityManager::attachComponent(const IEEntity& key, const unsigned long long component)
{
    if(!doesExist(key) || hasComponent(key, component))
        return false;

    entityMap[key] += component;

    return true;
}

bool IEEntityManager::detachComponent(const IEEntity& key, const unsigned long long component)
{
    if(!doesExist(key) || !hasComponent(key, component))
        return false;

    entityMap[key] -= component;

    return true;
}

bool IEEntityManager::doesExist(const IEEntity& key) const
{
    return entityMap.contains(key);
}

bool IEEntityManager::hasComponent(const IEEntity& key, const unsigned long long component) const
{
    if(!doesExist(key))
        return false;

    return ((entityMap[key] & component) == component);
}

unsigned long long IEEntityManager::getAttachComponents(const IEEntity& key) const
{
    if(!doesExist(key))
        return 0;

    return entityMap[key];
}
