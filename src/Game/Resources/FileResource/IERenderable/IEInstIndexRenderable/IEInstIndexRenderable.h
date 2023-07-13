#pragma once

#include <QVector>

#include "IEInstRenderable.h"
#include "IEIndexBufferObject.h"

struct IEInstIndexRenderableNode
{
    IEIndexBufferObject* IBO;

    IEInstIndexRenderableNode() :
        IBO(new IEIndexBufferObject())
    {

    }

    ~IEInstIndexRenderableNode()
    {
        IBO->destroy();
        delete IBO;
        IBO = nullptr;
    }
};

class IEInstIndexRenderable : public IEInstRenderable
{
    QVector<IEInstIndexRenderableNode*> instIndexNodes;

public:
    IEInstIndexRenderable(QObject* parent = nullptr);
    IEInstIndexRenderable(const QString& path, QObject* parent = nullptr);
    IEInstIndexRenderable(IERenderable* parent);
    virtual ~IEInstIndexRenderable();

protected:
    bool handleBuild(const int index) override;
    bool handleBuildRelease(const int index) override;
    void handleDraw(const int index, const QVector<std::any>& args) override;

public:
    virtual int appendNode(IERenderableNode* node) override;
    virtual bool removeNode(const int index) override;
    virtual void cleanup() override;

    IEInstIndexRenderableNode* getInstIndexNode(const int index);

    QVector<IEInstIndexRenderableNode*>& getInstIndexNodes() { return instIndexNodes; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

