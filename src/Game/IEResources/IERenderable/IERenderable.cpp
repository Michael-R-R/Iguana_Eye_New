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
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers(),
    isEdited(false)
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
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers(),
    isEdited(true)
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
    uniformData(other.uniformData),
    dirtyVec2Buffers(other.dirtyVec2Buffers), dirtyVec3Buffers(other.dirtyVec3Buffers),
    dirtyVec4Buffers(other.dirtyVec4Buffers), dirtyMat4Buffers(other.dirtyMat4Buffers),
    isEdited(other.isEdited)
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
    dirtyVec2Buffers.append(key);
}

void IERenderable::addVec3Buffer(const QString& key, IEVertexBuffer<QVector3D>* value)
{
    vec3BufferContainer->add(key, value);
    dirtyVec3Buffers.append(key);
}

void IERenderable::addVec4Buffer(const QString& key, IEVertexBuffer<QVector4D>* value)
{
    vec4BufferContainer->add(key, value);
    dirtyVec4Buffers.append(key);
}

void IERenderable::addMat4Buffer(const QString& key, IEVertexBuffer<QMatrix4x4>* value)
{
    mat4BufferContainer->add(key, value);
    dirtyMat4Buffers.append(key);
}

int IERenderable::appendVec2InstanceValue(const QString& key, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer)
        return -1;

    dirtyVec2Buffers.append(key);

    return buffer->appendBufferValue(value);
}

int IERenderable::appendVec3InstanceValue(const QString& key, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer)
        return -1;

    dirtyVec3Buffers.append(key);

    return buffer->appendBufferValue(value);
}

int IERenderable::appendVec4InstanceValue(const QString& key, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer)
        return -1;

    dirtyVec4Buffers.append(key);

    return buffer->appendBufferValue(value);
}

int IERenderable::appendMat4InstanceValue(const QString& key, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer)
        return -1;

    dirtyMat4Buffers.append(key);

    return buffer->appendBufferValue(value);
}

void IERenderable::removeVec2InstanceValue(const QString& key, const int index)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer)
        return;

    dirtyVec2Buffers.append(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec3InstanceValue(const QString& key, const int index)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer)
        return;

    dirtyVec3Buffers.append(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec4InstanceValue(const QString& key, const int index)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer)
        return;

    dirtyVec4Buffers.append(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeMat4InstanceValue(const QString& key, const int index)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer)
        return;

    dirtyMat4Buffers.append(key);

    buffer->removeBufferValue(index);
}

void IERenderable::setVec2InstanceValue(const QString& key, const int index, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index, &value);
}

void IERenderable::setVec3InstanceValue(const QString& key, const int index, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index, &value);
}

void IERenderable::setVec4InstanceValue(const QString& key, const int index, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index, &value);
}

void IERenderable::setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index, &value);
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

void IERenderable::checkForDirtyBuffers()
{
    foreach(auto& key, dirtyVec2Buffers)
        vec2BufferContainer->getValue(key)->reallocate();
    dirtyVec2Buffers.clear();

    foreach(auto& key, dirtyVec3Buffers)
        vec3BufferContainer->getValue(key)->reallocate();
    dirtyVec3Buffers.clear();

    foreach(auto& key, dirtyVec4Buffers)
        vec4BufferContainer->getValue(key)->reallocate();
    dirtyVec4Buffers.clear();

    foreach(auto& key, dirtyMat4Buffers)
        mat4BufferContainer->getValue(key)->reallocate();
    dirtyMat4Buffers.clear();
}
