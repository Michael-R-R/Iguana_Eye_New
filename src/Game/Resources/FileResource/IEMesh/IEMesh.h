#pragma once

#include <QVector>
#include <glm/glm.hpp>

#include "IEFileResource.h"

class IEMesh : public IEFileResource
{
protected:
    QVector<glm::vec3> positionVertices;
    QVector<glm::vec3> normalVertices;
    QVector<glm::vec2> textureVertices;
    QVector<glm::vec3> tangentVertices;
    QVector<glm::vec3> bitangentVertices;
    QVector<unsigned> indices;

    IEMesh* parent;
    QVector<IEMesh*> children;
    QVector<IEMesh*> meshes;

public:
    IEMesh(QObject* parent = nullptr);
    IEMesh(const QString& path, QObject* parent = nullptr);
    IEMesh(const IEMesh&) = delete;
    virtual ~IEMesh();

    bool operator==(const IEMesh& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMesh& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMesh& other) { return IEResource::operator<(other); }
    bool operator>(const IEMesh& other) { return IEResource::operator>(other); }

    QVector<glm::vec3>& getPosVertices() { return positionVertices; }
    QVector<glm::vec3>& getNormVertices() { return normalVertices; }
    QVector<glm::vec2>& getTexVertices() { return textureVertices; }
    QVector<glm::vec3>& getTanVertices() { return tangentVertices; }
    QVector<glm::vec3>& getBiTanVertices() { return bitangentVertices; }
    QVector<unsigned>& getIndices() { return indices; }
    IEMesh* getParent() { return parent; }
    QVector<IEMesh*>& getChildren() { return children; }
    QVector<IEMesh*>& getMeshes() { return meshes; }

    void setPosVertices(const QVector<glm::vec3> val) { positionVertices = val; }
    void setNormVertices(const QVector<glm::vec3> val) { normalVertices = val; }
    void setTexVertices(const QVector<glm::vec2> val) { textureVertices = val; }
    void setTanVertices(const QVector<glm::vec3> val) { tangentVertices = val; }
    void setBiTanVertices(const QVector<glm::vec3> val) { bitangentVertices = val; }
    void setIndices(const QVector<unsigned> val) { indices = val; }
    void setParent(IEMesh* val) { parent = val; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};
