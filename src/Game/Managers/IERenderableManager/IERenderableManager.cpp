#include "IERenderableManager.h"
#include "GameStartEvent.h"
#include "IEScene.h"

IERenderableManager::IERenderableManager(QObject* parent) :
    IEManager(parent)
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

bool IERenderableManager::add(const unsigned long long key, IERenderable* value)
{
    if(!IEManager::add(key, value))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

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
    auto shaderManager = event.getScene()->getShaderManager();

    for(auto& renderable : resourceContainer->getResources())
    {
        auto shader = shaderManager->getValue(renderable->getShaderId());
        if(!shader)
            continue;
        renderable->build(shader);
    }
}
