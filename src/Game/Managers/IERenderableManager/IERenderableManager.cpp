#include "IERenderableManager.h"
#include "GameStartEvent.h"

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

    emit added(key);

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

QDataStream& operator<<(QDataStream& out, const IERenderableManager& manager)
{
    out << *manager.getResourceContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IERenderableManager& manager)
{
    IEResourceContainer<IERenderable>* container = manager.getResourceContainer();

    in >> *container;

    manager.setResourceContainer(container);

    return in;
}
