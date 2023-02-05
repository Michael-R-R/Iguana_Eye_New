#include "IEMesh.h"

IEMesh::IEMesh() :
    IEResource(0),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const unsigned long long id) :
    IEResource(id),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const IEMesh& other) :
    IEResource(0),
    positionVertices(other.positionVertices), normalVertices(other.normalVertices),
    textureVertices(other.textureVertices), tangentVertices(other.tangentVertices),
    bitangentVertices(other.bitangentVertices), indices(other.indices)
{

}

IEMesh::~IEMesh()
{

}

QDataStream& operator<<(QDataStream& out, const IEMesh& mesh)
{
    out << mesh.getId()
        << mesh.getPosVertices()
        << mesh.getNormVertices()
        << mesh.getTexVertices()
        << mesh.getTanVertices()
        << mesh.getBiTanVertices()
        << mesh.getIndices();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEMesh& mesh)
{
    unsigned long long id = 0;
    QVector<QVector3D> pos;
    QVector<QVector3D> normals;
    QVector<QVector2D> textures;
    QVector<QVector3D> tangents;
    QVector<QVector3D> bitangents;
    QVector<unsigned> indices;

    in >> id >> pos >> normals >> textures
       >> tangents >> bitangents >> indices;

    mesh.setId(id);
    mesh.setPosVertices(pos);
    mesh.setNormVertices(normals);
    mesh.setTexVertices(textures);
    mesh.setTanVertices(tangents);
    mesh.setBiTanVertices(bitangents);
    mesh.setIndices(indices);

    return in;
}
