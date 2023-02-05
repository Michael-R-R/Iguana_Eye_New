#include "IEMaterialManager.h"

IEMaterialManager::IEMaterialManager(QObject* parent) :
    IEManager(parent)
{

}

IEMaterialManager::~IEMaterialManager()
{

}

void IEMaterialManager::startup()
{
    // Not used
}

void IEMaterialManager::shutdown()
{
    resourceContainer->clear();
}

bool IEMaterialManager::add(const unsigned long long key, IEMaterial* value)
{
    if(!IEManager::add(key, value))
        return false;

    emit added(key);

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

QDataStream& operator<<(QDataStream& out, const IEMaterialManager& manager)
{
    out << *manager.getResourceContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEMaterialManager& manager)
{
    IEResourceContainer<IEMaterial>* container = manager.getResourceContainer();

    in >> *container;

    manager.setResourceContainer(container);

    return in;
}
