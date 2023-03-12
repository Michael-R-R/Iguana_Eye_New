#include "IEShaderManager.h"
#include "GameStartEvent.h"

IEShaderManager::IEShaderManager() :
    IEResourceManager()
{

}

IEShaderManager::~IEShaderManager()
{

}

void IEShaderManager::startup(const GameStartEvent&)
{
    this->buildAllShaders();
}

void IEShaderManager::shutdown()
{
    clear();
}

bool IEShaderManager::add(const unsigned long long key, std::unique_ptr<IEShader> value)
{
    if(!value || doesExist(key))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IEShaderManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IEShaderManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEShaderManager::buildAllShaders()
{
    for(auto& i : resources)
    {
        i.second->build();
    }
}
