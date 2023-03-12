#include "IEMaterialManager.h"
#include "GameStartEvent.h"

IEMaterialManager::IEMaterialManager() :
    IEManager()
{

}

IEMaterialManager::~IEMaterialManager()
{

}

void IEMaterialManager::startup(const GameStartEvent&)
{
    // Not used
}

void IEMaterialManager::shutdown()
{
    resourceContainer->clear();
}

bool IEMaterialManager::add(const unsigned long long key, std::unique_ptr<IEMaterial> value)
{
    IEMaterial& temp = *value;
    if(!IEManager::add(key, std::move(value)))
        return false;

    if(temp.getType() == IEResource::Type::Game)
        emit added(key, temp.getFilePath());

    return true;
}

bool IEMaterialManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEMaterialManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}
