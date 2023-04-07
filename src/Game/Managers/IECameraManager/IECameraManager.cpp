#include "IECameraManager.h"
#include "IESerialize.h"

IECameraManager::IECameraManager() :
    IEResourceManager()
{

}

IECameraManager::~IECameraManager()
{

}

bool IECameraManager::add(const unsigned long long key, std::unique_ptr<IECamera> value)
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

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IECameraManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IECameraManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IECameraManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        auto& camera = *i.second;

        out << camera.getFilePath();

        IESerialize::write<IECamera>(camera.getFilePath(), &camera);
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IECameraManager&>(obj);

    int size = 0;
    in >> size;

    QString filePath = "";

    for(int i = 0; i < size; i++)
    {
        in >> filePath;

        auto camera = std::make_unique<IECamera>();
        if(!IESerialize::read<IECamera>(filePath, &(*camera)))
            continue;

        auto id = camera->getId();
        manager.add(id, std::move(camera));
    }

    return in;
}
