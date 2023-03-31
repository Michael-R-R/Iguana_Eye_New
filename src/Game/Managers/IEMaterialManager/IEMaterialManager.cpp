#include "IEMaterialManager.h"
#include "GameStartEvent.h"
#include "IEFile.h"
#include "IESerialize.h"

IEMaterialManager::IEMaterialManager() :
    IEResourceManager()
{

}

IEMaterialManager::~IEMaterialManager()
{

}

bool IEMaterialManager::add(const unsigned long long key, std::unique_ptr<IEMaterial> value)
{
    if(!value || doesExist(key))
        return false;

    if(value->getType() == IEResource::Type::Game)
        emit added(key, value->getFilePath());

    resources[key] = std::move(value);

    return true;
}

bool IEMaterialManager::remove(const unsigned long long key)
{
    if(!doesExist(key))
        return false;

    resources.erase(key);

    emit removed(key);

    return true;
}

bool IEMaterialManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!doesExist(oldKey) || doesExist(newKey))
        return false;

    auto temp = std::move(resources.at(oldKey));
    resources.erase(oldKey);
    resources[newKey] = std::move(temp);

    emit keyChanged(oldKey, newKey);

    return true;
}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        IEMaterial& material = *i.second;

        out << material.getType();

        if(material.getType() != IEResource::Type::Game)
            continue;

        if(material.getIsEdited())
        {
            if(!IEFile::doesPathExist(material.getFilePath()))
                IEFile::makePath(material.getFilePath());

            if(IESerialize::write<IEMaterial>(material.getFilePath(), &material))
                material.setIsEdited(false);
        }

        out << material.getFilePath();
    }

    return out;
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEMaterialManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    IEResource::Type type;
    QString filePath = "";

    for(int i = 0; i < size; i++)
    {
        in >> type;

        if(type != IEResource::Type::Game)
            continue;

        in >> filePath;

        auto material = std::make_unique<IEMaterial>();
        if(!IESerialize::read<IEMaterial>(filePath, &(*material)))
            continue;

        manager.add(material->getId(), std::move(material));
    }

    return in;
}
