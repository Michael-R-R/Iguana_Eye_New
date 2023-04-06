#include "IEMesh.h"

IEMesh::IEMesh() :
    IEResource("", 0),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    positionVertices(), normalVertices(),
    textureVertices(), tangentVertices(),
    bitangentVertices(), indices()
{

}

IEMesh::IEMesh(const IEMesh& other) :
    IEResource(other.filePath, other.id),
    positionVertices(other.positionVertices), normalVertices(other.normalVertices),
    textureVertices(other.textureVertices), tangentVertices(other.tangentVertices),
    bitangentVertices(other.bitangentVertices), indices(other.indices)
{

}

IEMesh::~IEMesh()
{

}
