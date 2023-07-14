#pragma once

#include "IERenderable.h"
#include "IEIndexBufferObject.h"

struct IEIndexRenderableNode
{
    IEIndexBufferObject* IBO;

    IEIndexRenderableNode() :
        IBO(new IEIndexBufferObject())
    {

    }

    ~IEIndexRenderableNode()
    {
        cleanup();
    }

    void cleanup()
    {
        IBO->destroy();
        delete IBO;
        IBO = nullptr;
    }

    friend QDataStream& operator<<(QDataStream& out, const IEIndexRenderableNode& node)
    {
        out << *node.IBO;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEIndexRenderableNode& node)
    {
        in >> *node.IBO;
        return in;
    }
};

class IEIndexRenderable : public IERenderable
{
protected:
    QVector<IEIndexRenderableNode*> indexNodes;

public:
    IEIndexRenderable(QObject* parent = nullptr);
    IEIndexRenderable(const QString& path, QObject* parent = nullptr);
    IEIndexRenderable(IERenderable* parent);
    virtual ~IEIndexRenderable();

protected:
    bool handleBuild(const int index) override;
    bool handleBuildRelease(const int index) override;
    void handleDraw(const int index, const QVector<std::any>& args) override;

public:
    virtual int appendNode(IERenderableNode* node) override;
    virtual bool removeNode(const int index) override;
    virtual void cleanup() override;

    IEIndexRenderableNode* getIndexNode(const int index);

    QVector<IEIndexRenderableNode*>& getIndexNodes() { return indexNodes; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

