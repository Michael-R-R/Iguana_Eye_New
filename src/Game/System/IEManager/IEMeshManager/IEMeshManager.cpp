#include "IEMeshManager.h"
#include "IEMesh.h"
#include "IESerialize.h"

IEMeshManager::IEMeshManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEMeshManager::~IEMeshManager()
{

}

QDataStream& IEMeshManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const IEMeshManager& manager = static_cast<const IEMeshManager&>(obj);

    out << (int)manager.resources.size();

    foreach (auto* i, manager.resources)
    {
        out << i->getName();

        IESerialize::write<IEMesh>(i->getName(), static_cast<IEMesh*>(i));
    }

    return out;
}

QDataStream& IEMeshManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    IEMeshManager& manager = static_cast<IEMeshManager&>(obj);

    int count = 0;
    in >> count;

    QString path = "";
    for(int i = 0; i < count; i++)
    {
        in >> path;

        auto* mesh = new IEMesh(&manager);

        if(!IESerialize::read<IEMesh>(path, mesh))
        {
            delete mesh;
            continue;
        }

        if(!manager.add(mesh->getId(), mesh))
            delete mesh;
    }

    return in;
}
