#pragma once

#include <QDataStream>
#include <QOpenGLVertexArrayObject>

#include "IEResource.h"
#include "IEBuffer.h"

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

    IEBuffer* buffers;

public:
    IERenderable();
    IERenderable(const unsigned long long id);
    IERenderable(const IERenderable& other);
    ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    Type getType() const { return type; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }
    IEBuffer* getBuffers() const { return buffers; }

    void setType(const Type val) { type = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }
    void setBuffers(IEBuffer* val) { buffers = val; }
};

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable);
QDataStream& operator>>(QDataStream& in, IERenderable& renderable);
