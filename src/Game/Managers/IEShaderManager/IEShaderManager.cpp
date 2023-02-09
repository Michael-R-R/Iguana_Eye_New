#include "IEShaderManager.h"
#include "GameStartEvent.h"

IEShaderManager::IEShaderManager(QObject* parent) :
    IEManager(parent)
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

    emit added(key);

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

QDataStream& operator<<(QDataStream& out, const IEShaderManager& manager)
{
    out << *manager.getResourceContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEShaderManager& manager)
{
    IEResourceContainer<IEShader>* container = manager.getResourceContainer();

    in >> *container;

    manager.setResourceContainer(container);

    return in;
}
