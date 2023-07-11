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

void IEInstIndexRenderable::handleDraw(const QVector<std::any>&)
{
    if(!VAO || !IBO || shown < 1)
        return;

    VAO->bind();

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElementsInstanced(primitiveMode,
                                IBO->count(),
                                GL_UNSIGNED_INT,
                                0,
                                shown);
}

void IEInstIndexRenderable::addIboValues(const QVector<unsigned int>& vals)
{
    IBO->setValues(vals);
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
