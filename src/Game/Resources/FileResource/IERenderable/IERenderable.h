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
    QOpenGLVertexArrayObject* vao;
    QHash<QString, IEBufferObject*> buffers;
    QSet<QString> dirtyAllocations;

    IERenderableType type;
    GLenum primitiveMode;
    uint64_t meshId;
    uint64_t materialId;
    uint64_t shaderId;

    IERenderable* parent;
    QVector<IERenderable*> children;
    QVector<IERenderable*> renderables;

public:
    IERenderable(IERenderableType ieType, QObject* parent = nullptr);
    IERenderable(IERenderableType ieType,
                 const QString& path,
                 const uint64_t meID,
                 const uint64_t maID,
                 const uint64_t sID,
                 QObject* parent = nullptr);
    IERenderable(IERenderable* parent);
    IERenderable(const IERenderable&) = delete;
    virtual ~IERenderable();

    bool operator==(const IERenderable& other) { return IEFileResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEFileResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEFileResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEFileResource::operator>(other); }

protected:
    virtual bool handleBuild() = 0;
    virtual bool handleBuildRelease() = 0;
    virtual bool handleDraw(const QVector<std::any>& args) = 0;

public:
    virtual bool draw(const QVector<std::any>& args = QVector<std::any>{});

    bool bind();
    bool release();

    bool addBuffer(const QString& name, IEBufferObject* buffer);
    bool removeBuffer(const QString& name);
    bool appendBufferValue(const QString& name, const std::any& val);
    bool removeBufferValue(const QString& name, const int index);
    bool setBufferValue(const QString& name, const int index, const std::any& val);
    bool setBufferValues(const QString& name, const std::any& val);

    bool build(IEShader& shader);
    void updateDirtyBuffers();
    void cleanup();

    bool doesBufferExist(const QString& name);
    IEBufferObject* getBuffer(const QString& name);

    IERenderableType getType() const { return type; }
    GLenum getPrimitiveMode() const { return primitiveMode; }
    uint64_t getMeshId() const { return meshId; }
    uint64_t getMaterialId() const { return materialId; }
    uint64_t getShaderId() const { return shaderId; }
    IERenderable* getParent() { return parent; }
    QVector<IERenderable*>& getChildren() { return children; }
    QVector<IERenderable*>& getRenderables() { return renderables; }

    void setPrimitiveMode(const GLenum val) { primitiveMode = val; }
    void setMeshId(const uint64_t val) { meshId = val; }
    void setMaterialId(const uint64_t val) { materialId = val; }
    void setShaderId(const uint64_t val) { shaderId = val; }
    void setParent(IERenderable* val) { parent = val; }

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
