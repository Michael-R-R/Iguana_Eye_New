#pragma once

#include <QOpenGLVertexArrayObject>
#include <QString>
#include <QVector>
#include <QHash>
#include <QSet>
#include <any>
#include <gl/GL.h>

#include "IEFileResource.h"
#include "IEBufferObject.h"
#include "IEEnum.h"
#include "IEBufferObjectFactory.h"

class IEShader;

struct IERenderableNode
{
    QOpenGLVertexArrayObject* VAO;
    QHash<QString, IEBufferObject*> buffers;
    QSet<QString> dirtyAllocations;
    GLenum primitiveMode;

    IERenderableNode() :
        VAO(new QOpenGLVertexArrayObject()),
        buffers(),
        dirtyAllocations(),
        primitiveMode(GL_TRIANGLES)
    {

    }

    ~IERenderableNode()
    {
        cleanup();
    }

    void cleanup()
    {
        VAO->destroy();
        delete VAO;

        foreach (auto* buffer, buffers)
        {
            buffer->destroy();
            delete buffer;
        }

        buffers.clear();
        dirtyAllocations.clear();
    }

    friend QDataStream& operator<<(QDataStream& out, const IERenderableNode& node)
    {
        out << (int)node.buffers.size();
        QHashIterator<QString, IEBufferObject*> it(node.buffers);
        while(it.hasNext())
        {
            it.next();

            out << it.key()
                << it.value()->getBufferType()
                << *it.value();
        }

        out << node.dirtyAllocations << node.primitiveMode;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderableNode& node)
    {
        node.cleanup();

        node.VAO = new QOpenGLVertexArrayObject();

        int bufferCount = 0;
        in >> bufferCount;
        for(int i = 0; i < bufferCount; i++)
        {
            QString name = "";
            IEBufferType type = IEBufferType::Unknown;
            in >> name >> type;

            auto* buffer = IEBufferObjectFactory::make(type);
            if(!buffer) { continue; }

            in >> *buffer;

            node.buffers.insert(name, buffer);
        }

        in >> node.dirtyAllocations >> node.primitiveMode;

        return in;
    }
};

class IERenderable : public IEFileResource
{
protected:
    QVector<IERenderableNode*> nodes;

    uint64_t meshID;
    uint64_t materialID;
    uint64_t shaderID;

    IERenderableType type;

public:
    IERenderable(IERenderableType ieType, QObject* parent = nullptr);
    IERenderable(IERenderableType ieType, const QString& path, QObject* parent = nullptr);
    IERenderable(IERenderable* parent);
    IERenderable(const IERenderable&) = delete;
    virtual ~IERenderable();

    bool operator==(const IERenderable& other) { return IEFileResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEFileResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEFileResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEFileResource::operator>(other); }

protected:
    virtual bool handleBuild(const int index) = 0;
    virtual bool handleBuildRelease(const int index) = 0;
    virtual void handleDraw(const int index, const QVector<std::any>& args) = 0;

public:
    virtual void draw(const int index, const QVector<std::any>& args = QVector<std::any>{});
    virtual int appendNode(IERenderableNode* node);
    virtual bool removeNode(const int index);
    virtual void cleanup();

    IERenderableNode* getNode(const int index);

    bool addBuffer(const int index,
                   const QString& name,
                   const IEBufferType type,
                   const int s, const int o, const int d);
    bool removeBuffer(const int index, const QString& name);
    bool appendBufferValue(const int index, const QString& name, const std::any& val);
    bool removeBufferValue(const int index, const QString& name, const int bufferIndex);
    bool setBufferValue(const int index, const QString& name, const int bufferIndex, const std::any& val);
    bool setBufferValues(const int index, const QString& name, const std::any& val);
    bool doesBufferExist(const int index, const QString& name);
    void updateDirtyBuffers(const int index);
    IEBufferObject* getBuffer(const int index, const QString& name);

    bool build(const int index, IEShader& shader);

    QVector<IERenderableNode*>& getNodes() { return nodes; }
    IERenderableType getType() const { return type; }
    uint64_t getMeshID() const { return meshID; }
    uint64_t getMaterialID() const { return materialID; }
    uint64_t getShaderID() const { return shaderID; }

    void setMeshID(const uint64_t val) { meshID = val; }
    void setMaterialID(const uint64_t val) { materialID = val; }
    void setShaderID(const uint64_t val) { shaderID = val; }

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;

private:
    bool indexBoundsCheck(const int index);
};
