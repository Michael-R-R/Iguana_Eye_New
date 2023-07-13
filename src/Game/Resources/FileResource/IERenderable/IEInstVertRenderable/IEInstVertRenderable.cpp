#include "IEInstVertRenderable.h"
#include "IEBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstVertRenderable::IEInstVertRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Vertex, parent)
{

}

IEInstVertRenderable::IEInstVertRenderable(const QString& path, QObject* parent) :
    IEInstRenderable(IERenderableType::I_Vertex, path, parent)
{

}

IEInstVertRenderable::IEInstVertRenderable(IERenderable* parent) :
    IEInstRenderable(parent)
{

}

IEInstVertRenderable::~IEInstVertRenderable()
{

}

bool IEInstVertRenderable::handleBuild(const int)
{
    return true;
}

bool IEInstVertRenderable::handleBuildRelease(const int)
{
    return true;
}

void IEInstVertRenderable::handleDraw(const int index, const QVector<std::any>&)
{
    if(index < 0 || index >= nodes.size())
        return;

    if(shown < 1)
        return;

    IERenderableNode* rNode = nodes[index];
    IEBufferObject* buffer = rNode->buffers["aPos"];

    rNode->VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawArraysInstanced(rNode->primitiveMode,
                              0,
                              buffer->count(),
                              shown);
}

QDataStream& IEInstVertRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IEInstRenderable::serialize(out, obj);
}

QDataStream& IEInstVertRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    return IEInstRenderable::deserialize(in, obj);
}
