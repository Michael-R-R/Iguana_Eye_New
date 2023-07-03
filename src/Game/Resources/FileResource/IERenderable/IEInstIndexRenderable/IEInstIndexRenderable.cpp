#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>

IEInstIndexRenderable::IEInstIndexRenderable(QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, parent),
    IBOs()
{

}

IEInstIndexRenderable::IEInstIndexRenderable(IERenderableType ieType,
                                             const QString& path,
                                             const uint64_t mID, const uint64_t sID,
                                             QObject* parent) :
    IEInstRenderable(IERenderableType::I_Index, path, mID, sID, parent),
    IBOs()
{

}

IEInstIndexRenderable::~IEInstIndexRenderable()
{

}

void IEInstIndexRenderable::handleBuild(const int index)
{
    if(index < 0 || index >= IBOs.size())
        throw std::exception("IEInstIndexRenderable::handleBuild()::Index_out_of_bounds");

    IBOs[index]->build();
}

void IEInstIndexRenderable::handleBuildRelease(const int index)
{
    if(index < 0 || index >= IBOs.size())
        throw std::exception("IEInstIndexRenderable::handleBuildRelease()::Index_out_of_bounds");

    IBOs[index]->release();
}

void IEInstIndexRenderable::handleDraw(const int index, const QVector<std::any>&)
{
    auto* ibo = IBOs[index];

    auto* gl = QOpenGLContext::currentContext()->extraFunctions();
    gl->glDrawElementsInstanced(primitiveMode,
                               ibo->size(),
                               GL_UNSIGNED_INT,
                               0,
                               shown);
}

QDataStream& IEInstIndexRenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEInstRenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstIndexRenderable&>(obj);

    out << renderable.IBOs.size();
    foreach (auto* ibo, renderable.IBOs)
    {
        out << *ibo;
    }

    return out;
}

QDataStream& IEInstIndexRenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEInstRenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstIndexRenderable&>(obj);
    renderable.IBOs.clear();

    int size = 0;
    in >> size;
    for(int i = 0; i < size; i++)
    {
        auto* ibo = new IEIndexBufferObject(&renderable);
        in >> *ibo;

        renderable.IBOs.append(ibo);
    }

    return in;
}
