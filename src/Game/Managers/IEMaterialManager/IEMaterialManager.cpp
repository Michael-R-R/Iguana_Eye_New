#include "IEMaterialManager.h"
#include "IEMaterial.h"
#include "IEDefaultMaterial.h"
#include "IEFile.h"
#include "IESerialize.h"

IEMaterialManager::IEMaterialManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEMaterialManager::~IEMaterialManager()
{

}

void IEMaterialManager::startup()
{
    auto defaultMat = new IEDefaultMaterial(IEFile::absolutePath("./resources/materials/game/default.iemat"), this);
    defaultId = defaultMat->getId();
    this->add(defaultId, defaultMat);
}

QDataStream& IEMaterialManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IEMaterialManager&>(obj);

    out << (int)manager.resources.size();

    for(auto& i : manager.resources)
    {
        out << i->getFilePath();

        IESerialize::write<IEMaterial>(i->getFilePath(), static_cast<IEMaterial*>(i));
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
