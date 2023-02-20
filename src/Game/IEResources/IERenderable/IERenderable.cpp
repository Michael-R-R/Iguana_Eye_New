#include "IERenderable.h"
#include "IEShader.h"
IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(),
    IEResource("", 0),
    isRenderable(true),
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    indexBuffer(new IEIndexBuffer()),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>()),
    uniformData()
{

}

IERenderable::IERenderable(const QString& path, const unsigned long long id) :
    QOpenGLVertexArrayObject(),
    IEResource(path, id),
    isRenderable(true),
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    indexBuffer(new IEIndexBuffer()),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>()),
    uniformData()
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(),
    IEResource(other.filePath, other.id),
    isRenderable(other.isRenderable),
    renderType(other.renderType), drawMode(other.drawMode),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId),
    indexBuffer(new IEIndexBuffer(*other.indexBuffer)),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>(*other.vec2BufferContainer)),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>(*other.vec3BufferContainer)),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>(*other.vec4BufferContainer)),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>(*other.mat4BufferContainer)),
    uniformData(other.uniformData)
{

}

IERenderable::~IERenderable()
{
    delete indexBuffer;
    delete vec2BufferContainer;
    delete vec3BufferContainer;
    delete vec4BufferContainer;
    delete mat4BufferContainer;
    if(this->isCreated())
        this->destroy();
}

void IERenderable::addIndexBuffer(IEIndexBuffer* buffer)
{
    if(indexBuffer)
        delete indexBuffer;

    indexBuffer = buffer;
}

void IERenderable::addVec2Buffer(const QString& key, IEVertexBuffer<QVector2D>* value)
{
    vec2BufferContainer->add(key, value);
}

void IERenderable::addVec3Buffer(const QString& key, IEVertexBuffer<QVector3D>* value)
{
    vec3BufferContainer->add(key, value);
}

void IERenderable::addVec4Buffer(const QString& key, IEVertexBuffer<QVector4D>* value)
{
    vec4BufferContainer->add(key, value);
}

void IERenderable::addMat4Buffer(const QString& key, IEVertexBuffer<QMatrix4x4>* value)
{
    mat4BufferContainer->add(key, value);
}

void IERenderable::build(IEShader* shader)
{
    shader->bind();

    if(!this->isCreated())
        this->create();
    this->bind();

    indexBuffer->build();

    QMapIterator<QString, IEVertexBuffer<QVector2D>*> it2(vec2BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); it2.value()->build(shader->attributeLocation(it2.key())); }

    QMapIterator<QString, IEVertexBuffer<QVector3D>*> it3(vec3BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); it3.value()->build(shader->attributeLocation(it3.key())); }

    QMapIterator<QString, IEVertexBuffer<QVector4D>*> it4(vec4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); it4.value()->build(shader->attributeLocation(it4.key())); }

    QMapIterator<QString, IEVertexBuffer<QMatrix4x4>*> it5(mat4BufferContainer->getBuffers());
    while(it5.hasNext()) { it5.next(); it5.value()->build(shader->attributeLocation(it5.key())); }

    shader->release();
    this->release();
    indexBuffer->release();
    vec2BufferContainer->releaseAllBuffers();
    vec3BufferContainer->releaseAllBuffers();
    vec4BufferContainer->releaseAllBuffers();
    mat4BufferContainer->releaseAllBuffers();
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
