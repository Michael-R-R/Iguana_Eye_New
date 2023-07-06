#include "IEIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEIndexRenderable::IEIndexRenderable(QObject* parent) :
    IERenderable(IERenderableType::Index, parent),
    IBO(new IEIndexBufferObject(parent))
{

}

IEIndexRenderable::IEIndexRenderable(const QString& path, const uint64_t meID,
                                     const uint64_t maID, const uint64_t sID,
                                     QObject* parent) :
    IERenderable(IERenderableType::Index, path, meID, maID, sID, parent),
    IBO(new IEIndexBufferObject(parent))
{

}

IEIndexRenderable::IEIndexRenderable(IERenderable* parent) :
    IERenderable(parent),
    IBO(new IEIndexBufferObject(parent))
{

}

IEIndexRenderable::~IEIndexRenderable()
{
    if(IBO)
    {
        IBO->destroy();
        delete IBO;
        IBO = nullptr;
    }
}

bool IEIndexRenderable::handleBuild()
{
    if(!IBO)
        return false;

    IBO->build();

    return true;
}

bool IEIndexRenderable::handleBuildRelease()
{
    if(!IBO)
        return false;

    IBO->release();

    return true;
}

bool IEIndexRenderable::handleDraw(const QVector<std::any>&)
{
    if(!vao || !IBO)
        return false;

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElements(primitiveMode,
                       IBO->count(),
                       GL_UNSIGNED_INT,
                       0);

    return true;
}

QDataStream& IEIndexRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IERenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEIndexRenderable&>(obj);

    out << *renderable.IBO;

    return out;
}

QDataStream& IEIndexRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IERenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEIndexRenderable&>(obj);

    in >> *renderable.IBO;

    return in;
}
