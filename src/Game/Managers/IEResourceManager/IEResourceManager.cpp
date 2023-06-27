#include "IEResourceManager.h"
#include "IEResource.h"

IEResourceManager::IEResourceManager(QObject* parent) :
    IEObject(parent),
    resources(),
    defaultId(0)
{

}

IEResourceManager::~IEResourceManager()
{

}

bool IEResourceManager::add(const unsigned long long key, IEResource* value)
{
    if(!value || doesExist(key))
        return false;

    resources[key] = value;
    value->setParent(this);

    emit added(key, value->getName());

    return true;
}

bool IEResourceManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    auto* temp = resources[key];
    resources.remove(key);
    delete temp;

    emit removed(key);

    return true;
}

bool IEResourceManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = resources[oldKey];
    resources.remove(oldKey);
    resources[newKey] = temp;

    emit keyChanged(oldKey, newKey);

    return true;
}

bool IEResourceManager::doesExist(const unsigned long long key) const
{
    return resources.contains(key);
}

void IEResourceManager::clear()
{
    for(auto* i : resources)
    {
        delete i;
    }

    resources.clear();
}

QDataStream& IEResourceManager::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEResourceManager::deserialize(QDataStream& in, Serializable&)
{
    return in;
}
