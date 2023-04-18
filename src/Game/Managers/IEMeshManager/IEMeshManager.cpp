#include "IEMeshManager.h"
#include "IEMesh.h"
#include "IEObjImporter.h"

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

    for(auto* i : manager.resources)
    {
        out << *static_cast<IEMesh*>(i);
    }

    return out;
}

QDataStream& IEMeshManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEMeshManager& manager = static_cast<IEMeshManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    IEMesh* mesh = nullptr;

    for(int i = 0; i < size; i++)
    {
        mesh = new IEMesh(&manager);

        in >> *mesh;

        if(!IEObjImporter::importMesh(mesh->getFilePath(), *mesh))
        {
            delete mesh;
            continue;
        }

        if(!manager.add(mesh->getId(), mesh))
            delete mesh;
    }

    return in;
}
