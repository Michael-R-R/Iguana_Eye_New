#pragma once

#include <QVector2D>
#include <QVector3D>
#include <QVector>

#include "IEFileResource.h"

class IEMesh : public IEFileResource
{
protected:
    QVector<QVector3D> positionVertices;
    QVector<QVector3D> normalVertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector3D> tangentVertices;
    QVector<QVector3D> bitangentVertices;
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

    QVector<QVector3D>& getPosVertices() { return positionVertices; }
    QVector<QVector3D>& getNormVertices() { return normalVertices; }
    QVector<QVector2D>& getTexVertices() { return textureVertices; }
    QVector<QVector3D>& getTanVertices() { return tangentVertices; }
    QVector<QVector3D>& getBiTanVertices() { return bitangentVertices; }
    QVector<unsigned>& getIndices() { return indices; }
    IEMesh* getParent() { return parent; }
    QVector<IEMesh*>& getChildren() { return children; }
    QVector<IEMesh*>& getMeshes() { return meshes; }

    void setPosVertices(const QVector<QVector3D> val) { positionVertices = val; }
    void setNormVertices(const QVector<QVector3D> val) { normalVertices = val; }
    void setTexVertices(const QVector<QVector2D> val) { textureVertices = val; }
    void setTanVertices(const QVector<QVector3D> val) { tangentVertices = val; }
    void setBiTanVertices(const QVector<QVector3D> val) { bitangentVertices = val; }
    void setIndices(const QVector<unsigned> val) { indices = val; }
    void setParent(IEMesh* val) { parent = val; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};
