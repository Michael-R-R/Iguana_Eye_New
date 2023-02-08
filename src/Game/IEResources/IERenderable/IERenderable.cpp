#include "IERenderable.h"
#include "IEShader.h"
IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEBufferContainer<QMatrix4x4>())
{

}

IERenderable::IERenderable(const unsigned long long id) :
    QOpenGLVertexArrayObject(), IEResource(id),
    type(Type::None),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEBufferContainer<QMatrix4x4>())
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(), IEResource(0),
    type(other.type),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId),
    vec2BufferContainer(other.vec2BufferContainer),
    vec3BufferContainer(other.vec3BufferContainer),
    vec4BufferContainer(other.vec4BufferContainer),
    mat4BufferContainer(other.mat4BufferContainer)
{

}

IERenderable::~IERenderable()
{
    delete vec2BufferContainer;
    delete vec3BufferContainer;
    delete vec4BufferContainer;
    delete mat4BufferContainer;
    if(this->isCreated())
        this->destroy();
}

void IERenderable::build(IEShader* shader)
{
    shader->bind();

    if(!this->isCreated())
        this->create();
    this->bind();

    QMapIterator<QString, IEBuffer<QVector2D>*> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); it1.value()->build(shader->attributeLocation(it1.key())); }

    QMapIterator<QString, IEBuffer<QVector3D>*> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); it2.value()->build(shader->attributeLocation(it2.key())); }

    QMapIterator<QString, IEBuffer<QVector4D>*> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); it3.value()->build(shader->attributeLocation(it3.key())); }

    QMapIterator<QString, IEBuffer<QMatrix4x4>*> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); it4.value()->build(shader->attributeLocation(it4.key())); }

    vec2BufferContainer->releaseAllBuffers();
    vec3BufferContainer->releaseAllBuffers();
    vec4BufferContainer->releaseAllBuffers();
    mat4BufferContainer->releaseAllBuffers();
    this->release();
    shader->release();
}

QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
{
    out << renderable.getId()
        << renderable.getType()
        << renderable.getMeshId()
        << renderable.getMaterialId()
        << renderable.getShaderId()
        << *renderable.getVec2BufferContainer()
        << *renderable.getVec3BufferContainer()
        << *renderable.getVec4BufferContainer()
        << *renderable.getMat4BufferContainer();

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
    IEBufferContainer<QVector3D>* vec3BufferContainer = renderable.getVec3BufferContainer();
    IEBufferContainer<QVector4D>* vec4BufferContainer = renderable.getVec4BufferContainer();
    IEBufferContainer<QMatrix4x4>* mat4BufferContainer = renderable.getMat4BufferContainer();

    in >> id >> type >> meshId >> materialId >> shaderId
       >> *vec2BufferContainer
       >> *vec3BufferContainer
       >> *vec4BufferContainer
       >> *mat4BufferContainer;

    renderable.setId(id);
    renderable.setType(type);
    renderable.setMeshId(meshId);
    renderable.setMaterialId(materialId);
    renderable.setShaderId(shaderId);
    renderable.setVec2BufferContainer(vec2BufferContainer);
    renderable.setVec3BufferContainer(vec3BufferContainer);
    renderable.setVec4BufferContainer(vec4BufferContainer);
    renderable.setMat4BufferContainer(mat4BufferContainer);

    return in;
}
