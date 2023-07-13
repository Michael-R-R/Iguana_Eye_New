#include "IEVertRenderable.h"
#include "IEBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEVertRenderable::IEVertRenderable(QObject* parent) :
    IERenderable(IERenderableType::Vertex, parent)
{

}

IEVertRenderable::IEVertRenderable(const QString& path, QObject* parent) :
    IERenderable(IERenderableType::Vertex, path, parent)
{

}

IEVertRenderable::IEVertRenderable(IERenderable* parent) :
    IERenderable(parent)
{

}

IEVertRenderable::~IEVertRenderable()
{

}

bool IEVertRenderable::handleBuild(const int)
{
    return true;
}

bool IEVertRenderable::handleBuildRelease(const int)
{
    return true;
}

void IEVertRenderable::handleDraw(const int index, const QVector<std::any>&)
{
    if(index < 0 || index >= nodes.size())
        return;

    IERenderableNode* rNode = nodes[index];
    IEBufferObject* buffer = rNode->buffers["aPos"];

    rNode->VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawArrays(rNode->primitiveMode,
                     0,
                     buffer->count());
}

QDataStream& IEVertRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IERenderable::serialize(out, obj);
}

QDataStream& IEVertRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    return IERenderable::deserialize(in, obj);
}
