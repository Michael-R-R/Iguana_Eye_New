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
