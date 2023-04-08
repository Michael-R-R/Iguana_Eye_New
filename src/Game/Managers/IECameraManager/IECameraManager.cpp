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
    if(!value || doesExist(key))
        return false;

    emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IECameraManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.remove(key);

    emit removed(key);

    return true;
}

bool IECameraManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = resources[oldKey];
    resources.remove(oldKey);
    resources[newKey] = temp;

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IECameraManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IECameraManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IECameraManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto camera = QSharedPointer<IECamera>::create();

        in >> *camera;

        manager.add(camera->getId(), std::move(camera));
    }

    return in;
}
