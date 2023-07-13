#pragma once

#include <QVector>
#include <glm/glm.hpp>

#include "IEFileResource.h"

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
