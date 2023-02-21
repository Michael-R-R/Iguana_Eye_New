#pragma once

#include <QDataStream>
#include <QOpenGLVertexArrayObject>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <gl/GL.h>

#include "IEResource.h"
#include "IEIndexBuffer.h"
#include "IEVertexBufferContainer.h"
#include "IEUniform.h"

class IEShader;

class IERenderable : public QOpenGLVertexArrayObject, public IEResource
{
public:
    enum class RenderType
    {
        None, Vertex, Index, I_Vertex, I_Index
    };

protected:
    RenderType renderType;
    GLenum drawMode;
    bool isRenderable;

    unsigned long long meshId;
    unsigned long long materialId;
    unsigned long long shaderId;

    IEIndexBuffer* indexBuffer;
    IEVertexBufferContainer<QVector2D>* vec2BufferContainer;
    IEVertexBufferContainer<QVector3D>* vec3BufferContainer;
    IEVertexBufferContainer<QVector4D>* vec4BufferContainer;
    IEVertexBufferContainer<QMatrix4x4>* mat4BufferContainer;

    IEUniform uniformData;

public:
    IERenderable();
    IERenderable(const QString& path, const unsigned long long id);
    IERenderable(const IERenderable& other);
    ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    void addIndexBuffer(IEIndexBuffer* buffer);
    void addVec2Buffer(const QString& key, IEVertexBuffer<QVector2D>* value);
    void addVec3Buffer(const QString& key, IEVertexBuffer<QVector3D>* value);
    void addVec4Buffer(const QString& key, IEVertexBuffer<QVector4D>* value);
    void addMat4Buffer(const QString& key, IEVertexBuffer<QMatrix4x4>* value);

    void build(IEShader* shader);
    void bindUniformData(IEShader* shader);
    int instanceCount() const;

    RenderType getRenderType() const { return renderType; }
    GLenum getDrawMode() const { return drawMode; }
    bool getIsRenderable() const { return isRenderable; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }

    void setRenderType(const RenderType val) { renderType = val; }
    void setDrawType(const GLenum val) { drawMode = val; }
    void setIsRenderable(const bool val) { isRenderable = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }
    void setUniformData(const IEUniform& val) { uniformData = val; }

    friend QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
    {
        out << renderable.filePath
            << renderable.id
            << renderable.type
            << renderable.renderType
            << renderable.drawMode
            << renderable.isRenderable
            << renderable.meshId
            << renderable.materialId
            << renderable.shaderId
            << *renderable.indexBuffer
            << *renderable.vec2BufferContainer
            << *renderable.vec3BufferContainer
            << *renderable.vec4BufferContainer
            << *renderable.mat4BufferContainer
            << renderable.uniformData;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderable& renderable)
    {
        in >> renderable.filePath
           >> renderable.id
           >> renderable.type
           >> renderable.renderType
           >> renderable.drawMode
           >> renderable.isRenderable
           >> renderable.meshId
           >> renderable.materialId
           >> renderable.shaderId
           >> *renderable.indexBuffer
           >> *renderable.vec2BufferContainer
           >> *renderable.vec3BufferContainer
           >> *renderable.vec4BufferContainer
           >> *renderable.mat4BufferContainer
           >> renderable.uniformData;

        return in;
    }
};
