#include "IEMesh.h"

IEMesh::IEMesh(QObject* parent) :
    IEFileResource(parent),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices(),
    parent(nullptr), children(), meshes()
{

}

IEMesh::IEMesh(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices(),
    parent(nullptr), children(), meshes()
{

}

IEMesh::~IEMesh()
{

}

QDataStream& IEMesh::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IEFileResource::serialize(out, obj);
}

QDataStream& IEMesh::deserialize(QDataStream& in, IESerializable& obj)
{
    return IEFileResource::deserialize(in, obj);
}
