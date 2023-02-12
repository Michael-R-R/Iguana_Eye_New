#include "IERenderable.h"
#include "IEShader.h"
IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(), IEResource(0),
    renderType(RenderType::None), drawType(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEBufferContainer<QMatrix4x4>()),
    uniformData()
{

}

IERenderable::IERenderable(const unsigned long long id) :
    QOpenGLVertexArrayObject(), IEResource(id),
    renderType(RenderType::None), drawType(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    vec2BufferContainer(new IEBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEBufferContainer<QMatrix4x4>()),
    uniformData()
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(), IEResource(0),
    renderType(other.renderType), drawType(other.drawType),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId),
    vec2BufferContainer(other.vec2BufferContainer),
    vec3BufferContainer(other.vec3BufferContainer),
    vec4BufferContainer(other.vec4BufferContainer),
    mat4BufferContainer(other.mat4BufferContainer),
    uniformData(other.uniformData)
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

void IERenderable::bindUniformData(IEShader* shader)
{
    uniformData.bind(shader);
}

int IERenderable::instanceCount() const
{
    // TODO implement
    return 1;
}
