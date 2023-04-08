#include "IECameraManager.h"

IECameraManager::IECameraManager() :
    IEResourceManager()
{

}

IECameraManager::~IECameraManager()
{

}

bool IECameraManager::add(const unsigned long long key, QSharedPointer<IECamera> value)
{
    if(!IEResourceManager::add(key, value))
        return false;

    emit added(key, value->getFilePath());

    return true;
}

bool IECameraManager::remove(const unsigned long long key)
{
    if(!IEResourceManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IECameraManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEResourceManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IECameraManager::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResourceManager::serialize(out, obj);
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResourceManager::deserialize(in, obj);
}
