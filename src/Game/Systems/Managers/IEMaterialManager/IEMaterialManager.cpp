#include "IEMaterialManager.h"
#include "IEMaterial.h"
#include "IEFile.h"
#include "IESerialize.h"

IEMaterialManager::IEMaterialManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEMaterialManager::~IEMaterialManager()
{

}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : qAsConst(manager.resources))
    {
        out << i->getName();

        IESerialize::write<IEMaterial>(i->getName(), static_cast<IEMaterial*>(i));
    }

    return out;
}

QDataStream& IEMaterialManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IEMaterialManager&>(obj);

    int size = 0;
    in >> size;

    QString path = "";
    for(int i = 0; i < size; i++)
    {
        in >> path;

        auto* material = new IEMaterial(path, &manager);
        if(!IESerialize::read<IEMaterial>(path, material))
        {
            delete material;
            continue;
        }

        if(!manager.add(material->getId(), material))
            delete material;
    }

    return in;
}
