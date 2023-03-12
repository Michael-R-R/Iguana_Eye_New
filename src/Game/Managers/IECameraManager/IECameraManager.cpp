#include "IECameraManager.h"
#include "GameStartEvent.h"

IECameraManager::IECameraManager() :
    IEResourceManager()
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
    clear();
}

bool IECameraManager::add(const unsigned long long key, std::unique_ptr<IECamera> value)
{
    if(!value || doesExist(key))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IECameraManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IECameraManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}
