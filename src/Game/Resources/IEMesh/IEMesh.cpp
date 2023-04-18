#include "IEMesh.h"

IEMesh::IEMesh(QObject* parent) :
    IEResource(parent),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const QString& path, QObject* parent) :
    IEResource(path, parent),
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
