#include "IEMeshManager.h"
#include "IEObjImporter.h"

IEMeshManager::IEMeshManager() :
    IEResourceManager()
{

}

IEMeshManager::~IEMeshManager()
{

}

bool IEMeshManager::add(const unsigned long long key, QSharedPointer<IEMesh> value)
{
    if(!IEResourceManager::add(key, value))
        return false;

    emit added(key, value->getFilePath());

    return true;
}

bool IEMeshManager::remove(const unsigned long long key)
{
    if(!IEResourceManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEMeshManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEResourceManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEMeshManager::importAll()
{
    QVector<unsigned long long> markedForRemove;

    for(auto& i : resources)
    {
        if(!IEObjImporter::importMesh(i->getFilePath(), *i))
        {
            markedForRemove.push_back(i->getId());
            continue;
        }
    }

    for(auto& i : markedForRemove)
    {
        IEMeshManager::remove(i);
    }
}

QDataStream& IEMeshManager::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResourceManager::serialize(out, obj);
}

QDataStream& IEMeshManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    IEMeshManager& manager = static_cast<IEMeshManager&>(obj);
    manager.importAll();

    return in;
}
