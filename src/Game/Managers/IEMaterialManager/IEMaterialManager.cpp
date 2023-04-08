#include "IEMaterialManager.h"

IEMaterialManager::IEMaterialManager() :
    IEResourceManager()
{

}

IEMaterialManager::~IEMaterialManager()
{

}

bool IEMaterialManager::add(const unsigned long long key, QSharedPointer<IEMaterial> value)
{
    if(!IEResourceManager::add(key, value))
        return false;

    emit added(key, value->getFilePath());

    return true;
}

bool IEMaterialManager::remove(const unsigned long long key)
{
    if(!IEResourceManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEMaterialManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEResourceManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResourceManager::serialize(out, obj);
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResourceManager::deserialize(in, obj);
}
