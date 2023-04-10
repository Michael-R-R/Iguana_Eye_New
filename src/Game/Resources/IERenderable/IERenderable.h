#pragma once

#include <QOpenGLVertexArrayObject>
#include <QSharedPointer>
#include <QSet>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QGenericMatrix>
#include <gl/GL.h>

#include "IEResource.h"
#include "IEIndexBuffer.h"
#include "IEVertexBufferContainer.h"
#include "IEUniform.h"

class IEShader;

class IERenderable : public QOpenGLVertexArrayObject, public IEResource
{
public:
    enum class RenderMode
    {
        None, Vertex, I_Vertex, Index, I_Index
    };

protected:
    RenderMode renderMode;
    GLenum drawMode;

    unsigned long long meshId;
    unsigned long long materialId;
    unsigned long long shaderId;

    QSharedPointer<IEIndexBuffer> indexBuffer;
    QSharedPointer<IEVertexBufferContainer<QVector2D>> vec2BufferContainer;
    QSharedPointer<IEVertexBufferContainer<QVector3D>> vec3BufferContainer;
    QSharedPointer<IEVertexBufferContainer<QVector4D>> vec4BufferContainer;
    QSharedPointer<IEVertexBufferContainer<QGenericMatrix<4,4,float>>> mat4BufferContainer;
    int shownCount;
    int hiddenCount;

    IEUniform uniformData;

    QSet<QString> dirtyVec2Buffers;
    QSet<QString> dirtyVec3Buffers;
    QSet<QString> dirtyVec4Buffers;
    QSet<QString> dirtyMat4Buffers;

public:
    IERenderable();
    IERenderable(const QString& path,
                 const unsigned long long meshId_,
                 const unsigned long long materialId_,
                 const unsigned long long shaderId_);
    IERenderable(const IERenderable&) = delete;
    ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    void addIndexBuffer(QSharedPointer<IEIndexBuffer> buffer);
    void addVec2Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector2D>> value);
    void addVec3Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector3D>> value);
    void addVec4Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector4D>> value);
    void addMat4Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QGenericMatrix<4,4,float>>> value);
    void setVec2BufferData(const QString& key, const QVector<QVector2D>& data);
    void setVec3BufferData(const QString& key, const QVector<QVector3D>& data);
    void setVec4BufferData(const QString& key, const QVector<QVector4D>& data);
    void setMat4BufferData(const QString& key, const QVector<QGenericMatrix<4,4,float>>& data);

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
                                QMap<QString, QGenericMatrix<4,4,float>>& mat4Data);

    void appendVec2InstanceValue(const QString& key, const QVector2D& value);
    void appendVec3InstanceValue(const QString& key, const QVector3D& value);
    void appendVec4InstanceValue(const QString& key, const QVector4D& value);
    void appendMat4InstanceValue(const QString& key, const QGenericMatrix<4,4,float>& value);
    void removeVec2InstanceValue(const QString& key, const int index);
    void removeVec3InstanceValue(const QString& key, const int index);
    void removeVec4InstanceValue(const QString& key, const int index);
    void removeMat4InstanceValue(const QString& key, const int index);
    void setVec2InstanceValue(const QString& key, const int index, const QVector2D& value);
    void setVec3InstanceValue(const QString& key, const int index, const QVector3D& value);
    void setVec4InstanceValue(const QString& key, const int index, const QVector4D& value);
    void setMat4InstanceValue(const QString& key, const int index, const QGenericMatrix<4,4,float>& value);

    void build(IEShader& shader);
    void bindUniformData(IEShader& shader);
    void checkForDirtyBuffers();
    bool equals(const unsigned long long meshId,
                const unsigned long long materialId,
                const unsigned long long shaderId);

    RenderMode getRenderMode() const { return renderMode; }
    GLenum getDrawMode() const { return drawMode; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }

    void setRenderMode(const RenderMode val) { renderMode = val; }
    void setDrawType(const GLenum val) { drawMode = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }
    void setUniformData(const IEUniform& val) { uniformData = val; }

private:
    void appendInstanceValues();
    void purgeInstanceValues(const int index);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
