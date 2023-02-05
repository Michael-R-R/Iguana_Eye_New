#include "IEMeshManager.h"

IEMeshManager::IEMeshManager(QObject* parent) :
    IEManager(parent)
{

}

IEMeshManager::~IEMeshManager()
{

}

void IEMeshManager::startup()
{
    // Not used
}

void IEMeshManager::shutdown()
{
    resourceContainer->clear();
}

bool IEMeshManager::add(const unsigned long long key, IEMesh* value)
{
    if(!IEManager::add(key, value))
        return false;

    emit added(key);

    return true;
}

bool IEMeshManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEMeshManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& operator<<(QDataStream& out, const IEMeshManager& manager)
{
    out << *manager.getResourceContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEMeshManager& manager)
{
    IEResourceContainer<IEMesh>* container = manager.getResourceContainer();

    in >> *container;

    manager.setResourceContainer(container);

    return in;
}
