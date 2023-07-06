#include "IEResourceManager.h"
#include "IEResource.h"

IEResourceManager::IEResourceManager(QObject* parent) :
    IESystem(parent),
    resources()
{

}

IEResourceManager::~IEResourceManager()
{

}

void IEResourceManager::shutdown(IEGame&)
{
    cleanup();
}

void IEResourceManager::onDeserialize(IEGame&)
{
    cleanup();
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

void IEResourceManager::cleanup()
{
    for(auto* i : qAsConst(resources))
    {
        delete i;
        i = nullptr;
    }

    resources.clear();
}

QDataStream& IEResourceManager::serialize(QDataStream& out, const IESerializable&) const
{
    return out;
}

QDataStream& IEResourceManager::deserialize(QDataStream& in, IESerializable&)
{
    return in;
}
