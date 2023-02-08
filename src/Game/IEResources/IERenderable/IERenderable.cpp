#include "IERenderable.h"
#include "IEShader.h"
IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec3BufferContainer(new IEBufferContainer<QVector3D>())
{

}

IERenderable::IERenderable(const unsigned long long id) :
    QOpenGLVertexArrayObject(), IEResource(id),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec3BufferContainer(new IEBufferContainer<QVector3D>())
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(other.type),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId), vec3BufferContainer(other.vec3BufferContainer)
{

}

IERenderable::~IERenderable()
{
    delete vec3BufferContainer;
}

void IERenderable::build(IEShader* shader)
{
    shader->bind();
    this->create();
    this->bind();

    QMapIterator<QString, IEBuffer<QVector3D>*> it1(vec3BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); it1.value()->rebuild(shader->attributeLocation(it1.key())); }

    vec3BufferContainer->releaseAll();
    this->release();
    shader->release();
}

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
{
    out << renderable.getId() << renderable.getType()
        << renderable.getMeshId() << renderable.getMaterialId()
        << renderable.getShaderId()
        << *renderable.getVec3BufferContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IERenderable& renderable)
{
    unsigned long long id = 0;
    IERenderable::Type type = IERenderable::Type::None;
    unsigned long long meshId = 0;
    unsigned long long materialId = 0;
    unsigned long long shaderId = 0;
    IEBufferContainer<QVector3D>* vec2BufferContainer = renderable.getVec3BufferContainer();

    in >> id >> type >> meshId >> materialId >> shaderId
       >> *vec2BufferContainer;

    renderable.setId(id);
    renderable.setType(type);
    renderable.setMeshId(meshId);
    renderable.setMaterialId(materialId);
    renderable.setShaderId(shaderId);
    renderable.setVec3BufferContainer(vec2BufferContainer);

    return in;
}
