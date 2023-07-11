#include "IEInstVertRenderable.h"
#include "IEBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstVertRenderable::IEInstVertRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Vertex, parent)
{

}

IEInstVertRenderable::IEInstVertRenderable(const QString& path,
                                           const uint64_t meID,
                                           const uint64_t maID,
                                           const uint64_t sID,
                                           QObject* parent) :
    IEInstRenderable(IERenderableType::I_Vertex, path, meID, maID, sID, parent)
{

}

IEInstVertRenderable::IEInstVertRenderable(IERenderable* parent) :
    IEInstRenderable(parent)
{

}

IEInstVertRenderable::~IEInstVertRenderable()
{

}

bool IEInstVertRenderable::handleBuild()
{
    return true;
}

bool IEInstVertRenderable::handleBuildRelease()
{
    return true;
}

void IEInstVertRenderable::handleDraw(const QVector<std::any>&)
{
    IEBufferObject* buffer = this->getBuffer("aPos");
    if(!VAO || !buffer || shown < 1)
        return;

    VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawArraysInstanced(primitiveMode,
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
