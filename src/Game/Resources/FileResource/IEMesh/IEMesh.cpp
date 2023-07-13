#include "IEMesh.h"
#include "IESerializeConverter.h"

IEMesh::IEMesh(QObject* parent) :
    IEFileResource(parent),
    nodes()
{

}

IEMesh::IEMesh(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    nodes()
{

}

IEMesh::~IEMesh()
{
    cleanup();
}

int IEMesh::appendNode(IEMeshNode* node)
{
    if(!node) { return -1; }

    const int index = nodes.size();

    nodes.append(node);

    return index;
}

void IEMesh::remove(const int index)
{
    if(index < 0 || index >= nodes.size())
        return;

    auto* temp = nodes[index];
    nodes.removeAt(index);
    delete temp;
}

IEMeshNode* IEMesh::getNode(const int index)
{
    if(index < 0 || index >= nodes.size())
        return nullptr;

    return nodes[index];
}

void IEMesh::cleanup()
{
     foreach(auto* i, nodes)
    {
        delete i;
        i = nullptr;
    }

    nodes.clear();
}

QDataStream& IEMesh::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& mesh = static_cast<const IEMesh&>(obj);

    // TODO implement

    return out;
}

QDataStream& IEMesh::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& mesh = static_cast<IEMesh&>(obj);

    // TODO implement

    return in;
}
