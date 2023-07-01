#pragma once

#include <QOpenGLVertexArrayObject>
#include <QString>
#include <QVector>
#include <QHash>
#include <QSet>
#include <gl/GL.h>

#include "IEFileResource.h"
#include "IEUniformData.h"

class IEShader;
class IEBufferObject;

class IERenderable : public IEFileResource
{

protected:
    QVector<QOpenGLVertexArrayObject*> VAOs;
    QVector<QHash<QString, IEBufferObject*>> buffers;
    QVector<QSet<QString>> dirtyAllocations;

    GLenum primitiveMode;
    uint64_t materialId;
    uint64_t shaderId;

    IEUniformData uData;

public:
    IERenderable(QObject* parent = nullptr);
    IERenderable(const QString& path,
                 const uint64_t mID,
                 const uint64_t sID,
                 QObject* parent = nullptr);
    IERenderable(const IERenderable&) = delete;
    virtual ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

protected:
    virtual void handleDraw(const int index) = 0;
    virtual void handleBuild(const int index) = 0;
    virtual void handleBuildRelease(const int index) = 0;

public:
    virtual void draw(const int index);

    void bind(const int index);
    void bindData(IEShader& shader);

    int addVAO();
    void addBuffer(const int index, const QString& name, IEBufferObject* buffer);
    void removeBuffer(const QString& name);
    void build(IEShader& shader);
    void updateDirtyBuffers(const int index);
    void cleanup();

    bool doesBufferExist(const int index, const QString& name);

    GLenum getPrimitiveMode() const { return primitiveMode; }
    uint64_t getMaterialId() const { return materialId; }
    uint64_t getShaderId() const { return shaderId; }
    const IEUniformData& getUniformData() const { return uData; }

    void setPrimitiveMode(const GLenum val) { primitiveMode = val; }
    void setMaterialId(const uint64_t val) { materialId = val; }
    void setShaderId(const uint64_t val) { shaderId = val; }
    void setUniformData(const IEUniformData& val) { uData = val; }

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
