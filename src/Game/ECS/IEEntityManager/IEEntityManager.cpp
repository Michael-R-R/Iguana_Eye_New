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
        while(doesEntityExist(entity))
        {
            entity = IEEntity(++nextId);
        }
    }

    entityMap[entity] = QSet<size_t>();

    return entity;
}

bool IEEntityManager::remove(const IEEntity key)
{
    if(!doesEntityExist(key))
        return false;

    entityMap.remove(key);
    freeIdStack.push(key.getId());

    return true;
}

bool IEEntityManager::attachComponent(const IEEntity& key, const size_t& component)
{
    if(hasComponent(key, component))
        return false;

    entityMap[key].insert(component);

    return true;
}

bool IEEntityManager::detachComponent(const IEEntity& key, const size_t& component)
{
    if(!hasComponent(key, component))
        return false;

    entityMap[key].remove(component);

    return true;
}

bool IEEntityManager::doesEntityExist(const IEEntity& key) const
{
    return entityMap.contains(key);
}

bool IEEntityManager::hasComponent(const IEEntity& key, const size_t& component) const
{
    if(!doesEntityExist(key))
        return false;

    return entityMap[key].contains(component);
}

QSet<size_t> IEEntityManager::getAttachedComponents(const IEEntity& key) const
{
    if(!doesEntityExist(key))
        return QSet<size_t>();

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
