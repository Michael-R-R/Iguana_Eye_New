#include "IEMesh.h"

IEMesh::IEMesh() :
    IEResource(),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const QString& path) :
    IEResource(path),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::~IEMesh()
{

}


QDataStream& IEMesh::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResource::serialize(out, obj);
}

QDataStream& IEMesh::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResource::deserialize(in, obj);
}
