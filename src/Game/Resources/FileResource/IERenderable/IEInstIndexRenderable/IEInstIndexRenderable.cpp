#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstIndexRenderable::IEInstIndexRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, parent),
    IBO(nullptr)
{

}

IEInstIndexRenderable::IEInstIndexRenderable(const QString& path,
                                             const uint64_t meID,
                                             const uint64_t maID,
                                             const uint64_t sID,
                                             QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, path, meID, maID, sID, parent),
    IBO(nullptr)
{

}

IEInstIndexRenderable::IEInstIndexRenderable(IERenderable* parent) :
    IEInstRenderable(IERenderableType::I_Index,
                     parent->getName(),
                     parent->getMeshId(),
                     parent->getMaterialId(),
                     parent->getShaderId(),
                     parent),
    IBO(nullptr)
{
    this->parent = parent;
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

void IEInstIndexRenderable::handleBuild()
{
    if(!IBO)
        throw std::exception("IEInstIndexRenderable::handleBuild()::nullptr");

    IBO->build();
}

void IEInstIndexRenderable::handleBuildRelease()
{
    if(!IBO)
        throw std::exception("IEInstIndexRenderable::handleBuildRelease()::nullptr");

    IBO->release();
}

void IEInstIndexRenderable::handleDraw(const QVector<std::any>&)
{
    if(shown < 1)
        return;

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElementsInstanced(primitiveMode,
                                IBO->count(),
                                GL_UNSIGNED_INT,
                                0,
                                shown);
}

void IEInstIndexRenderable::addIBO(IEIndexBufferObject* ibo)
{
    if(IBO)
    {
        IBO->destroy();
        delete IBO;
        IBO = nullptr;
    }

    IBO = ibo;
    IBO->setParent(this);
}

QDataStream& IEInstIndexRenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEInstRenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstIndexRenderable&>(obj);

    out << *renderable.IBO;

    return out;
}

QDataStream& IEInstIndexRenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEInstRenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstIndexRenderable&>(obj);

    auto* ibo = new IEIndexBufferObject(&renderable);
    in >> *ibo;

    renderable.IBO = ibo;

    return in;
}
