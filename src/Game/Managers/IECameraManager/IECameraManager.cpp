#include "IECameraManager.h"
#include "IESerialize.h"

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
    const auto& manager = static_cast<const IECameraManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        const QString& path = i->getFilePath();

        out << path;

        IESerialize::write<IECamera>(path, &(*i));
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IECameraManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    QString path = "";
    for(int i = 0; i < size; i++)
    {
        in >> path;

        auto resource = QSharedPointer<IECamera>::create(path);
        if(!IESerialize::read<IECamera>(path, &(*resource)))
            continue;

        manager.add(resource->getId(), resource);
    }

    return in;
}
