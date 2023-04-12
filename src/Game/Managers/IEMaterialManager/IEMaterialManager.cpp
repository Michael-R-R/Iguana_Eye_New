#include "IEMaterialManager.h"
#include "IEDefaultMaterial.h"
#include "IEFile.h"
#include "IESerialize.h"

IEMaterialManager::IEMaterialManager() :
    IEResourceManager()
{
    auto defaultMat = QSharedPointer<IEDefaultMaterial>::create(IEFile::absolutePath("./resources/materials/game/default.iemat"));
    defaultId = defaultMat->getId();
    IEMaterialManager::add(defaultId, defaultMat);
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
    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        const QString& path = i->getFilePath();

        out << path;

        IESerialize::write<IEMaterial>(path, &(*i));
    }

    return out;
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEMaterialManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    QString path = "";
    for(int i = 0; i < size; i++)
    {
        in >> path;

        auto resource = QSharedPointer<IEMaterial>::create(path);
        if(!IESerialize::read<IEMaterial>(path, &(*resource)))
            continue;

        manager.add(resource->getId(), resource);
    }

    return in;
}
