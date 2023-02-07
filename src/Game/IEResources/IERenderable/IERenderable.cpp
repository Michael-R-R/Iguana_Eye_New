#include "IERenderable.h"
#include "IEShader.h"
IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>())
{

}

IERenderable::IERenderable(const unsigned long long id) :
    QOpenGLVertexArrayObject(), IEResource(id),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>())
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(other.type),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId), vec2BufferContainer(other.vec2BufferContainer)
{

}

IERenderable::~IERenderable()
{
    delete vec2BufferContainer;
}

void IERenderable::rebuildAllBuffers(IEShader* shader)
{
    QMapIterator<QString, IEBuffer<QVector2D>*> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); it1.value()->rebuild(shader->attributeLocation(it1.key())); }
}

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
{
    out << renderable.getId() << renderable.getType()
        << renderable.getMeshId() << renderable.getMaterialId()
        << renderable.getShaderId()
        << *renderable.getVec2BufferContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IERenderable& renderable)
{
    unsigned long long id = 0;
    IERenderable::Type type = IERenderable::Type::None;
    unsigned long long meshId = 0;
    unsigned long long materialId = 0;
    unsigned long long shaderId = 0;
    IEBufferContainer<QVector2D>* vec2BufferContainer = renderable.getVec2BufferContainer();

    in >> id >> type >> meshId >> materialId >> shaderId
       >> *vec2BufferContainer;

    renderable.setId(id);
    renderable.setType(type);
    renderable.setMeshId(meshId);
    renderable.setMaterialId(materialId);
    renderable.setShaderId(shaderId);
    renderable.setVec2BufferContainer(vec2BufferContainer);

    return in;
}
