#pragma once

#include <QDataStream>
#include <QVector2D>
#include <QVector3D>
#include <QVector>

#include "IEResource.h"

class IEMesh : public IEResource
{
    QVector<QVector3D> positionVertices;
    QVector<QVector3D> normalVertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector3D> tangentVertices;
    QVector<QVector3D> bitangentVertices;
    QVector<unsigned> indices;

public:
    IEMesh();
    IEMesh(const unsigned long long id);
    IEMesh(const IEMesh& other);
    ~IEMesh();

    bool operator==(const IEMesh& other) { return IEResource::operator==(other); }
    bool operator!=(const IEMesh& other) { return IEResource::operator!=(other); }
    bool operator<(const IEMesh& other) { return IEResource::operator<(other); }
    bool operator>(const IEMesh& other) { return IEResource::operator>(other); }

    const QVector<QVector3D>& getPosVertices() const { return positionVertices; }
    const QVector<QVector3D>& getNormVertices() const { return normalVertices; }
    const QVector<QVector2D>& getTexVertices() const { return textureVertices; }
    const QVector<QVector3D>& getTanVertices() const { return tangentVertices; }
    const QVector<QVector3D>& getBiTanVertices() const { return bitangentVertices; }
    const QVector<unsigned>& getIndices() const { return indices; }

    void setPosVertices(const QVector<QVector3D> val) { positionVertices = val; }
    void setNormVertices(const QVector<QVector3D> val) { normalVertices = val; }
    void setTexVertices(const QVector<QVector2D> val) { textureVertices = val; }
    void setTanVertices(const QVector<QVector3D> val) { tangentVertices = val; }
    void setBiTanVertices(const QVector<QVector3D> val) { bitangentVertices = val; }
    void setIndices(const QVector<unsigned> val) { indices = val; }
};

QDataStream& operator<<(QDataStream& out, const IEMesh& mesh);
QDataStream& operator>>(QDataStream& in, IEMesh& mesh);
