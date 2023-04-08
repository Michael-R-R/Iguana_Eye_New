#include "IEMaterialManager.h"
#include "IEFile.h"
#include "IESerialize.h"

IEMaterialManager::IEMaterialManager() :
    IEResourceManager()
{

}

IEMaterialManager::~IEMaterialManager()
{

}

bool IEMaterialManager::add(const unsigned long long key, QSharedPointer<IEMaterial> value)
{
    if(!value || doesExist(key))
        return false;

    emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IEMaterialManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.remove(key);

    emit removed(key);

    return true;
}

bool IEMaterialManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = resources[oldKey];
    resources.remove(oldKey);
    resources[newKey] = temp;

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEMaterialManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto material = QSharedPointer<IEMaterial>::create();

        in >> *material;

        manager.add(material->getId(), material);
    }

    return in;
}
