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
    IEResource::serialize(out, obj);

    const IEMesh& mesh = static_cast<const IEMesh&>(obj);

    out << mesh.positionVertices << mesh.normalVertices
        << mesh.textureVertices << mesh.tangentVertices
        << mesh.bitangentVertices << mesh.indices;

    return out;
}

QDataStream& IEMesh::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource::deserialize(in, obj);

    IEMesh& mesh = static_cast<IEMesh&>(obj);

    in >> mesh.positionVertices >> mesh.normalVertices
       >> mesh.textureVertices >> mesh.tangentVertices
       >> mesh.bitangentVertices >> mesh.indices;

    return in;
}
