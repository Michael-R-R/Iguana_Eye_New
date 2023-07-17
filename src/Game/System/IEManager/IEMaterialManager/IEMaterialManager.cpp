#include "IEMaterialManager.h"
#include "IEMaterial.h"

IEMaterialManager::IEMaterialManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEMaterialManager::~IEMaterialManager()
{

}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    foreach(auto* i, manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    auto& manager = static_cast<IEMaterialManager&>(obj);

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        auto* material = new IEMaterial(&manager);
        in >> *material;

        if(!manager.add(material->getID(), material))
            delete material;
    }

    return in;
}
