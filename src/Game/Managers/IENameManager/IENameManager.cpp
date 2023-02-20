#include "IENameManager.h"
#include "GameStartEvent.h"
#include "IEHash.h"

IENameManager::IENameManager(QObject* parent) :
    IEManager(parent)
{

}

IENameManager::~IENameManager()
{

}

void IENameManager::startup(const GameStartEvent&)
{
    // Not used
}

void IENameManager::shutdown()
{
    resourceContainer->clear();
}

bool IENameManager::add(const unsigned long long key, QString* value)
{
    if(!IEManager::add(key, value))
    {
        delete value;
        return false;
    }

    emit added(key);

    return true;
}

bool IENameManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IENameManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}
