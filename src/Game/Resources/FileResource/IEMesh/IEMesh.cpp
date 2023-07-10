#include "IEMesh.h"
#include "IESerializeConverter.h"

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
    IEFileResource::serialize(out, obj);

    const auto& mesh = static_cast<const IEMesh&>(obj);

    IESerializeConverter::write(out, mesh.positionVertices);
    IESerializeConverter::write(out, mesh.normalVertices);
    IESerializeConverter::write(out, mesh.textureVertices);
    IESerializeConverter::write(out, mesh.tangentVertices);
    IESerializeConverter::write(out, mesh.bitangentVertices);

    out << mesh.indices;

    return out;
}

QDataStream& IEMesh::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& mesh = static_cast<IEMesh&>(obj);

    IESerializeConverter::read(in, mesh.positionVertices);
    IESerializeConverter::read(in, mesh.normalVertices);
    IESerializeConverter::read(in, mesh.textureVertices);
    IESerializeConverter::read(in, mesh.tangentVertices);
    IESerializeConverter::read(in, mesh.bitangentVertices);

    in >> mesh.indices;

    return in;
}
