#include "IERenderable.h"

IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    buffers(new IEBuffer())
{

}

IERenderable::IERenderable(const unsigned long long id) :
    QOpenGLVertexArrayObject(), IEResource(id),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    buffers(new IEBuffer())
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(other.type),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId), buffers(other.buffers)
{

}

IERenderable::~IERenderable()
{
    delete buffers;
}

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
{
    out << renderable.getId() << renderable.getType()
        << renderable.getMeshId() << renderable.getMaterialId()
        << renderable.getShaderId() << *renderable.getBuffers();

    return out;
}

QDataStream& operator>>(QDataStream& in, IERenderable& renderable)
{
    unsigned long long id = 0;
    IERenderable::Type type = IERenderable::Type::None;
    unsigned long long meshId = 0;
    unsigned long long materialId = 0;
    unsigned long long shaderId = 0;
    IEBuffer* buffers = renderable.getBuffers();

    in >> id >> type >> meshId >> materialId
       >> shaderId >> *buffers;

    renderable.setId(id);
    renderable.setType(type);
    renderable.setMeshId(meshId);
    renderable.setMaterialId(materialId);
    renderable.setShaderId(shaderId);
    renderable.setBuffers(buffers);

    return in;
}
