#include "IEMeshManager.h"
#include "GameStartEvent.h"

IEMeshManager::IEMeshManager(QObject* parent) :
    IEManager(parent)
{

}

IEMeshManager::~IEMeshManager()
{

}

void IEMeshManager::startup(const GameStartEvent&)
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

    if(value->getType() == IEResource::RsrcType::Game)
        emit added(key, value->getFilePath());

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
