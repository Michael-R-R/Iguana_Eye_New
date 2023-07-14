#pragma once

#include <QVector>
#include <glm/glm.hpp>

#include "IEFileResource.h"
#include "IESerializeConverter.h"

struct IEMeshNode
{
    QVector<glm::vec3> positions;
    QVector<glm::vec3> normals;
    QVector<glm::vec2> textures;
    QVector<glm::vec3> tangents;
    QVector<glm::vec3> bitangents;
    QVector<unsigned> indices;

    IEMeshNode() :
        positions(), normals(),
        textures(), tangents(),
        bitangents(), indices()
    {

    }

    friend QDataStream& operator<<(QDataStream& out, const IEMeshNode& node)
    {
        IESerializeConverter::write(out, node.positions);
        IESerializeConverter::write(out, node.normals);
        IESerializeConverter::write(out, node.textures);
        IESerializeConverter::write(out, node.tangents);
        IESerializeConverter::write(out, node.bitangents);
        out << node.indices;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMeshNode& node)
    {
        IESerializeConverter::read(in, node.positions);
        IESerializeConverter::read(in, node.normals);
        IESerializeConverter::read(in, node.textures);
        IESerializeConverter::read(in, node.tangents);
        IESerializeConverter::read(in, node.bitangents);
        in >> node.indices;

        return in;
    }
};

class IEMesh : public IEFileResource
{
protected:
    QVector<IEMeshNode*> nodes;

public:
    IEMesh(QObject* parent = nullptr);
    IEMesh(const QString& path, QObject* parent = nullptr);
    IEMesh(const IEMesh&) = delete;
    virtual ~IEMesh();

    bool operator==(const IEMesh& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMesh& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMesh& other) { return IEResource::operator<(other); }
    bool operator>(const IEMesh& other) { return IEResource::operator>(other); }

    int appendNode(IEMeshNode* node);
    void remove(const int index);
    IEMeshNode* getNode(const int index);
    void cleanup();

    const QVector<IEMeshNode*>& getNodes() const { return nodes; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};
