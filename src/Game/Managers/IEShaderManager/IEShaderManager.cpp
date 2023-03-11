#include "IEShaderManager.h"
#include "GameStartEvent.h"

IEShaderManager::IEShaderManager() :
    IEManager()
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
    resourceContainer->clear();
}

bool IEShaderManager::add(const unsigned long long key, IEShader* value)
{
    if(!IEManager::add(key, value))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    return true;
}

bool IEShaderManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEShaderManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEShaderManager::buildAllShaders()
{
    for(auto& shader : resourceContainer->getResources())
    {
        shader->build();
    }
}
