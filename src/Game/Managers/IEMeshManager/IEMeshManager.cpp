#include "IEMeshManager.h"
#include "IEObjImporter.h"

IEMeshManager::IEMeshManager() :
    IEResourceManager()
{

}

IEMeshManager::~IEMeshManager()
{

}

bool IEMeshManager::add(const unsigned long long key, std::unique_ptr<IEMesh> value)
{
    if(!value || doesExist(key))
        return false;

    emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IEMeshManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IEMeshManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IEMeshManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEMeshManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << *i.second;
    }

    return out;
}

QDataStream& IEMeshManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEMeshManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto mesh = std::make_unique<IEMesh>();
        in >> *mesh;

        unsigned long long id = mesh->getId();
        manager.add(id, std::move(mesh));
    }

    return in;
}
