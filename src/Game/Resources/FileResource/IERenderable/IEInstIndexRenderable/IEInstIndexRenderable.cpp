#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstIndexRenderable::IEInstIndexRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, parent),
    IBO(new IEIndexBufferObject(this))
{

}

IEInstIndexRenderable::IEInstIndexRenderable(const QString& path,
                                             const uint64_t meID,
                                             const uint64_t maID,
                                             const uint64_t sID,
                                             QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, path, meID, maID, sID, parent),
    IBO(new IEIndexBufferObject(this))
{

}

IEInstIndexRenderable::IEInstIndexRenderable(IERenderable* parent) :
    IEInstRenderable(parent),
    IBO(new IEIndexBufferObject(this))
{

}

IEInstIndexRenderable::~IEInstIndexRenderable()
{
    if(IBO)
    {
        IBO->destroy();
        delete IBO;
        IBO = nullptr;
    }
}

bool IEInstIndexRenderable::handleBuild()
{
    if(!IBO)
        return false;

    IBO->build();

    return true;
}

bool IEInstIndexRenderable::handleBuildRelease()
{
    if(!IBO)
        return false;

    IBO->release();

    return true;
}

bool IEInstIndexRenderable::handleDraw(const QVector<std::any>&)
{
    if(shown < 1 || !vao || !IBO)
        return false;

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElementsInstanced(primitiveMode,
                                IBO->count(),
                                GL_UNSIGNED_INT,
                                0,
                                shown);

    return true;
}

void IEInstIndexRenderable::addIBO(IEIndexBufferObject* ibo)
{
    if(IBO)
    {
        IBO->destroy();
        delete IBO;
    }

    IBO = ibo;
    IBO->setParent(this);
}

QDataStream& IEInstIndexRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEInstRenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstIndexRenderable&>(obj);

    out << *renderable.IBO;

    return out;
}

QDataStream& IEInstIndexRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IEInstRenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstIndexRenderable&>(obj);

    in >> *renderable.IBO;

    return in;
}
