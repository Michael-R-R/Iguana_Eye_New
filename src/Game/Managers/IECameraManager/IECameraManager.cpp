#include "IECameraManager.h"
#include "GameStartEvent.h"

IECameraManager::IECameraManager(QObject* parent) :
    IEManager(parent)
{

}

IECameraManager::~IECameraManager()
{

}

void IECameraManager::startup(const GameStartEvent&)
{
    // Not used
}

void IECameraManager::shutdown()
{
    resourceContainer->clear();
}

bool IECameraManager::add(const unsigned long long key, IECamera* value)
{
    if(!IEManager::add(key, value))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    return true;
}

bool IECameraManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IECameraManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}
