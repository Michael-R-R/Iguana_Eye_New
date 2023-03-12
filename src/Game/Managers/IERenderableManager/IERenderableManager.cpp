#include "IERenderableManager.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEShaderManager.h"

IERenderableManager::IERenderableManager() :
    IEManager()
{

}

IERenderableManager::~IERenderableManager()
{

}

void IERenderableManager::startup(const GameStartEvent& event)
{
    this->buildAllRenderables(event);
}

void IERenderableManager::shutdown()
{
    resourceContainer->clear();
}

bool IERenderableManager::add(const unsigned long long key, std::unique_ptr<IERenderable> value)
{
    IERenderable& temp = *value;
    if(!IEManager::add(key, std::move(value)))
        return false;

    if(temp.getType() == IEResource::Type::Game)
        emit added(key, temp.getFilePath());

    return true;
}

bool IERenderableManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IERenderableManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

void IERenderableManager::buildAllRenderables(const GameStartEvent& event)
{
    auto& shaderManager = event.getScene().getShaderManager();

    for(auto& i : *resourceContainer->getResources())
    {
        auto* shader = shaderManager.getValue(i.second->getShaderId());
        if(!shader)
            continue;

        i.second->build(*shader);
    }
}
