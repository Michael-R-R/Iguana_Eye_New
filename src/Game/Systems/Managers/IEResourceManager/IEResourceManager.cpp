#include "IEResourceManager.h"
#include "IEResource.h"

IEResourceManager::IEResourceManager(QObject* parent) :
    IEGameSystem(parent),
    resources(),
    defaultId(0)
{

}

IEResourceManager::~IEResourceManager()
{

}

void IEResourceManager::shutdown(IEGame&)
{
    clear();
}

void IEResourceManager::onDeserialize(IEGame&)
{
    clear();
}

bool IEResourceManager::add(const uint64_t key, IEResource* value)
{
    if(!value || doesExist(key))
        return false;

    resources[key] = value;
    value->setParent(this);

    emit added(key, value->getName());

    return true;
}

bool IEResourceManager::remove(const uint64_t key)
{
    if(!doesExist(key))
        return false;

    auto* temp = resources[key];
    resources.remove(key);
    delete temp;

    emit removed(key);

    return true;
}

bool IEResourceManager::changeKey(const uint64_t oldKey, const uint64_t newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = resources[oldKey];
    resources.remove(oldKey);
    resources[newKey] = temp;

    emit keyChanged(oldKey, newKey);

    return true;
}

bool IEResourceManager::doesExist(const uint64_t key) const
{
    return resources.contains(key);
}

void IEResourceManager::clear()
{
    for(auto* i : qAsConst(resources))
    {
        delete i;
        i = nullptr;
    }

    resources.clear();
    defaultId = 0;
}

QDataStream& IEResourceManager::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEResourceManager::deserialize(QDataStream& in, Serializable&)
{
    return in;
}
