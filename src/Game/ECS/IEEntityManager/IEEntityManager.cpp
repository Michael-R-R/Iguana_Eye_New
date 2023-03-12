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
    freeIdStack.push(key.getId());

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

int IEEntityManager::count() const
{
    return entityMap.size();
}

QDataStream& IEEntityManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEEntityManager&>(obj);

    out << manager.entityMap
        << manager.freeIdStack
        << manager.nextId;

    return out;
}

QDataStream& IEEntityManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEEntityManager&>(obj);

    in >> manager.entityMap
       >> manager.freeIdStack
       >> manager.nextId;

    return in;
}
