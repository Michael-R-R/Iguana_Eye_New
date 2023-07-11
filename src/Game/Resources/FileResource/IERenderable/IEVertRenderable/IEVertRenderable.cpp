#include "IEVertRenderable.h"
#include "IEBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEVertRenderable::IEVertRenderable(QObject* parent) :
    IERenderable(IERenderableType::Vertex, parent)
{

}

IEVertRenderable::IEVertRenderable(const QString& path, const uint64_t meID,
                                   const uint64_t maID, const uint64_t sID,
                                   QObject* parent) :
    IERenderable(IERenderableType::Vertex, path, meID, maID, sID, parent)
{

}

IEVertRenderable::IEVertRenderable(IERenderable* parent) :
    IERenderable(parent)
{

}

IEVertRenderable::~IEVertRenderable()
{

}

bool IEVertRenderable::handleBuild()
{
    return true;
}

bool IEVertRenderable::handleBuildRelease()
{
    return true;
}

void IEVertRenderable::handleDraw(const QVector<std::any>&)
{
    auto* buffer = this->getBuffer("aPos");
    if(!VAO || !buffer)
        return;

    VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawArrays(primitiveMode,
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
