#pragma once

#include <QOpenGLVertexArrayObject>
#include <QString>
#include <QVector>
#include <QHash>
#include <QSet>
#include <any>
#include <gl/GL.h>

#include "IEFileResource.h"
#include "IEUniformData.h"
#include "IEEnum.h"

class IEShader;
class IEBufferObject;

class IERenderable : public IEFileResource
{
protected:
    QVector<QOpenGLVertexArrayObject*> VAOs;
    QVector<QHash<QString, IEBufferObject*>> buffers;
    QVector<QSet<QString>> dirtyAllocations;

    IERenderableType type;
    GLenum primitiveMode;
    uint64_t materialId;
    uint64_t shaderId;

public:
    IERenderable(IERenderableType ieType, QObject* parent = nullptr);
    IERenderable(IERenderableType ieType,
                 const QString& path,
                 const uint64_t mID,
                 const uint64_t sID,
                 QObject* parent = nullptr);
    IERenderable(const IERenderable&) = delete;
    virtual ~IERenderable();

    bool operator==(const IERenderable& other) { return IEFileResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEFileResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEFileResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEFileResource::operator>(other); }

protected:
    virtual void handleBuild(const int index) = 0;
    virtual void handleBuildRelease(const int index) = 0;
    virtual void handleDraw(const int index, const QVector<std::any>& args) = 0;

public:
    virtual void draw(const int index, const QVector<std::any>& args = QVector<std::any>{});

    void bind(const int index);
    void release(const int index);

    int addVAO();
    void addBuffer(const int index, const QString& name, IEBufferObject* buffer);
    void removeBuffer(const QString& name);
    void addBufferValue(const QString& name, const std::any& val, int index = 0);
    void removeBufferValue(const QString& name, const int bufferIndex, int index = 0);
    void setBufferValue(const QString& name, const int bufferIndex, const std::any& val, int index = 0);
    void setBufferValues(const QString& name, const std::any& val, int index = 0);
    void build(IEShader& shader);
    void updateDirtyBuffers(const int index);
    void cleanup();

    bool doesBufferExist(const int index, const QString& name);
    IEBufferObject* getBuffer(const int index, const QString& name);

    IERenderableType getRenderableType() const { return type; }
    GLenum getPrimitiveMode() const { return primitiveMode; }
    uint64_t getMaterialId() const { return materialId; }
    uint64_t getShaderId() const { return shaderId; }
    int getVaoSize() const { return VAOs.size(); }

    void setPrimitiveMode(const GLenum val) { primitiveMode = val; }
    void setMaterialId(const uint64_t val) { materialId = val; }
    void setShaderId(const uint64_t val) { shaderId = val; }

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
