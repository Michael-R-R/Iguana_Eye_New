#pragma once

#include <QOpenGLVertexArrayObject>
#include <QSet>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <gl/GL.h>

#include "IEFileResource.h"
#include "IEIndexBuffer.h"
#include "IEVertexBufferContainer.h"
#include "IEUniform.h"

class IEShader;

class IERenderable : public IEFileResource
{
public:
    enum class RenderMode
    {
        None, Vertex, I_Vertex, Index, I_Index
    };

protected:
    RenderMode renderMode;
    GLenum drawMode;

    uint64_t meshId;
    uint64_t materialId;
    uint64_t shaderId;

    QOpenGLVertexArrayObject* vao;
    IEIndexBuffer* indexBuffer;
    IEVertexBufferContainer<QVector2D>* vec2BufferContainer;
    IEVertexBufferContainer<QVector3D>* vec3BufferContainer;
    IEVertexBufferContainer<QVector4D>* vec4BufferContainer;
    IEVertexBufferContainer<QMatrix4x4>* mat4BufferContainer;
    int shownCount;
    int hiddenCount;

    IEUniform uniformData;

    QSet<QString> dirtyVec2Buffers;
    QSet<QString> dirtyVec3Buffers;
    QSet<QString> dirtyVec4Buffers;
    QSet<QString> dirtyMat4Buffers;

public:
    IERenderable(QObject* parent = nullptr);
    IERenderable(const QString& path,
                 const uint64_t meshId_,
                 const uint64_t materialId_,
                 const uint64_t shaderId_,
                 QObject* parent = nullptr);
    IERenderable(const IERenderable&) = delete;
    virtual ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    void bind() { vao->bind(); }
    void release() { vao->release(); }

    void addIndexBuffer(IEIndexBuffer* buffer);
    bool addVec2Buffer(const QString& key, IEVertexBuffer<QVector2D>* value);
    bool addVec3Buffer(const QString& key, IEVertexBuffer<QVector3D>* value);
    bool addVec4Buffer(const QString& key, IEVertexBuffer<QVector4D>* value);
    bool addMat4Buffer(const QString& key, IEVertexBuffer<QMatrix4x4>* value);
    void setVec2BufferData(const QString& key, const QVector<QVector2D>& data);
    void setVec3BufferData(const QString& key, const QVector<QVector3D>& data);
    void setVec4BufferData(const QString& key, const QVector<QVector4D>& data);
    void setMat4BufferData(const QString& key, const QVector<QMatrix4x4>& data);

    int addShownInstance();
    int addHiddenInstance();
    void removeShownInstance(const int index);
    void removeHiddenInstance();
    int shownInstanceCount() const;
    int hiddenInstanceCount() const;
    void fetchBufferDataAtIndex(const int index,
                                QMap<QString, QVector2D>& vec2Data,
                                QMap<QString, QVector3D>& vec3Data,
                                QMap<QString, QVector4D>& vec4Data,
                                QMap<QString, QMatrix4x4>& mat4Data);

    void appendVec2InstanceValue(const QString& key, const QVector2D& value);
    void appendVec3InstanceValue(const QString& key, const QVector3D& value);
    void appendVec4InstanceValue(const QString& key, const QVector4D& value);
    void appendMat4InstanceValue(const QString& key, const QMatrix4x4& value);
    void removeVec2InstanceValue(const QString& key, const int index);
    void removeVec3InstanceValue(const QString& key, const int index);
    void removeVec4InstanceValue(const QString& key, const int index);
    void removeMat4InstanceValue(const QString& key, const int index);
    void setVec2InstanceValue(const QString& key, const int index, const QVector2D& value);
    void setVec3InstanceValue(const QString& key, const int index, const QVector3D& value);
    void setVec4InstanceValue(const QString& key, const int index, const QVector4D& value);
    void setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value);

    void build(IEShader& shader);
    void bindUniformData(IEShader& shader);
    void checkForDirtyBuffers();
    bool equals(const uint64_t meshId,
                const uint64_t materialId,
                const uint64_t shaderId);

    RenderMode getRenderMode() const { return renderMode; }
    GLenum getDrawMode() const { return drawMode; }
    uint64_t getMeshId() const { return meshId; }
    uint64_t getMaterialId() const { return materialId; }
    uint64_t getShaderId() const { return shaderId; }

    void setRenderMode(const RenderMode val) { renderMode = val; }
    void setDrawType(const GLenum val) { drawMode = val; }
    void setMeshId(const uint64_t val) { meshId = val; }
    void setMaterialId(const uint64_t val) { materialId = val; }
    void setShaderId(const uint64_t val) { shaderId = val; }
    void setUniformData(const IEUniform& val) { uniformData = val; }

private:
    void appendInstanceValues();
    void purgeInstanceValues(const int index);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
