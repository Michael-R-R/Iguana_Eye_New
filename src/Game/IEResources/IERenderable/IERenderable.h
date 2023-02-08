#pragma once

#include <QDataStream>
#include <QOpenGLVertexArrayObject>
#include <QVector2D>

#include "IEResource.h"
#include "IEBufferContainer.h"

class IEShader;

class IERenderable : public QOpenGLVertexArrayObject, public IEResource
{
public:
    enum class Type
    {
        None, Vertex, Index
    };

private:
    Type type;
    unsigned long long meshId;
    unsigned long long materialId;
    unsigned long long shaderId;

    IEBufferContainer<QVector3D>* vec3BufferContainer;

public:
    IERenderable();
    IERenderable(const unsigned long long id);
    IERenderable(const IERenderable& other);
    ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    void build(IEShader* shader);

    Type getType() const { return type; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }
    IEBufferContainer<QVector3D>* getVec3BufferContainer() const { return vec3BufferContainer; }

    void setType(const Type val) { type = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }
    void setVec3BufferContainer(IEBufferContainer<QVector3D>* val) { vec3BufferContainer = val; }
};

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable);
QDataStream& operator>>(QDataStream& in, IERenderable& renderable);
