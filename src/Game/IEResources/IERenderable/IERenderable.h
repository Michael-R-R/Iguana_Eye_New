#pragma once

#include <QDataStream>
#include <QOpenGLVertexArrayObject>
#include <QSet>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <gl/GL.h>

#include "IEResource.h"
#include "IEIndexBuffer.h"
#include "IEVertexBufferContainer.h"
#include "IEInstanceData.h"
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
    IEInstanceData instanceData;

    IEUniform uniformData;

    QSet<QString> dirtyVec2Buffers;
    QSet<QString> dirtyVec3Buffers;
    QSet<QString> dirtyVec4Buffers;
    QSet<QString> dirtyMat4Buffers;

    bool isEdited;

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

    int addInstance(const IEEntity entity);
    std::tuple<IEEntity, int> removeInstance(const IEEntity entity);
    int instanceCount() const;
    int lookUpInstanceIndex(const IEEntity& entity);
    void purgeInstanceValues(const int index);

    int appendVec2InstanceValue(const QString& key, const QVector2D& value);
    int appendVec3InstanceValue(const QString& key, const QVector3D& value);
    int appendVec4InstanceValue(const QString& key, const QVector4D& value);
    int appendMat4InstanceValue(const QString& key, const QMatrix4x4& value);
    void removeVec2InstanceValue(const QString& key, const int index);
    void removeVec3InstanceValue(const QString& key, const int index);
    void removeVec4InstanceValue(const QString& key, const int index);
    void removeMat4InstanceValue(const QString& key, const int index);
    void setVec2InstanceValue(const QString& key, const int index, const QVector2D& value);
    void setVec3InstanceValue(const QString& key, const int index, const QVector3D& value);
    void setVec4InstanceValue(const QString& key, const int index, const QVector4D& value);
    void setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value);

    void build(IEShader* shader);
    void bindUniformData(IEShader* shader);
    void checkForDirtyBuffers();

    RenderType getRenderType() const { return renderType; }
    GLenum getDrawMode() const { return drawMode; }
    bool getIsRenderable() const { return isRenderable; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }
    bool getIsEdited() const { return isEdited; }

    void setRenderType(const RenderType val) { renderType = val; }
    void setDrawType(const GLenum val) { drawMode = val; }
    void setIsRenderable(const bool val) { isRenderable = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }
    void setUniformData(const IEUniform& val) { uniformData = val; }
    void setIsEdited(const bool val) { isEdited = val; }

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
            << renderable.instanceData
            << renderable.uniformData
            << renderable.isEdited;

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
           >> renderable.instanceData
           >> renderable.uniformData
           >> renderable.isEdited;

        return in;
    }
};
