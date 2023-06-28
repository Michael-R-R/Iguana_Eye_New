#include "IEMeshManager.h"
#include "IEMesh.h"
#include "IEMeshImport.h"

IEMeshManager::IEMeshManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IEMeshManager::~IEMeshManager()
{

}

QDataStream& IEMeshManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEMeshManager& manager = static_cast<const IEMeshManager&>(obj);

    out << (int)manager.resources.size();

    for(auto* i : qAsConst(manager.resources))
    {
        out << i->getName();
    }

    return out;
}

QDataStream& IEMeshManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEMeshManager& manager = static_cast<IEMeshManager&>(obj);

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        QString path = "";

        in >> path;

        auto* mesh = new IEMesh(path, &manager);

        if(!IEMeshImport::importMesh(path, *mesh))
        {
            delete mesh;
            continue;
        }

        if(!manager.add(mesh->getId(), mesh))
            delete mesh;
    }

    return in;
}
