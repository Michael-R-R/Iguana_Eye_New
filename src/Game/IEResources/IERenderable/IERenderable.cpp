#include "IERenderable.h"
#include "IEShader.h"

IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(),
    IEResource("", 0),
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    indexBuffer(new IEIndexBuffer()),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>()),
    shownCount(0), hiddenCount(0),
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers(),
    isEdited(false)
{

}

IERenderable::IERenderable(const QString& path,
                           const unsigned long long id,
                           const unsigned long long meshId_,
                           const unsigned long long materialId_,
                           const unsigned long long shaderId_) :
    QOpenGLVertexArrayObject(),
    IEResource(path, id),
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(meshId_), materialId(materialId_), shaderId(shaderId_),
    indexBuffer(new IEIndexBuffer()),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>()),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>()),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>()),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>()),
    shownCount(0), hiddenCount(0),
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers(),
    isEdited(true)
{

}

IERenderable::IERenderable(const IERenderable& other) :
    QOpenGLVertexArrayObject(),
    IEResource(other.filePath, other.id),
    renderType(other.renderType), drawMode(other.drawMode),
    meshId(other.meshId), materialId(other.materialId),
    shaderId(other.shaderId),
    indexBuffer(new IEIndexBuffer(*other.indexBuffer)),
    vec2BufferContainer(new IEVertexBufferContainer<QVector2D>(*other.vec2BufferContainer)),
    vec3BufferContainer(new IEVertexBufferContainer<QVector3D>(*other.vec3BufferContainer)),
    vec4BufferContainer(new IEVertexBufferContainer<QVector4D>(*other.vec4BufferContainer)),
    mat4BufferContainer(new IEVertexBufferContainer<QMatrix4x4>(*other.mat4BufferContainer)),
    shownCount(other.shownCount), hiddenCount(other.hiddenCount),
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
    dirtyVec2Buffers.insert(key);
}

void IERenderable::addVec3Buffer(const QString& key, IEVertexBuffer<QVector3D>* value)
{
    vec3BufferContainer->add(key, value);
    dirtyVec3Buffers.insert(key);
}

void IERenderable::addVec4Buffer(const QString& key, IEVertexBuffer<QVector4D>* value)
{
    vec4BufferContainer->add(key, value);
    dirtyVec4Buffers.insert(key);
}

void IERenderable::addMat4Buffer(const QString& key, IEVertexBuffer<QMatrix4x4>* value)
{
    mat4BufferContainer->add(key, value);
    dirtyMat4Buffers.insert(key);
}

void IERenderable::setVec2BufferData(const QString& key, const QVector<QVector2D>& data)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec2Buffers.insert(key);
}

void IERenderable::setVec3BufferData(const QString& key, const QVector<QVector3D>& data)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec3Buffers.insert(key);
}

void IERenderable::setVec4BufferData(const QString& key, const QVector<QVector4D>& data)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec4Buffers.insert(key);
}

void IERenderable::setMat4BufferData(const QString& key, const QVector<QMatrix4x4>& data)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyMat4Buffers.insert(key);
}

int IERenderable::addShownInstance()
{
    return shownCount++;
}

int IERenderable::addHiddenInstance()
{
    return hiddenCount++;
}

void IERenderable::removeShownInstance(const int index)
{
    shownCount--;

    this->purgeInstanceValues(index);
}

void IERenderable::removeHiddenInstance()
{
    hiddenCount--;
}

int IERenderable::shownInstanceCount() const
{
    return shownCount;
}

int IERenderable::hiddenInstanceCount() const
{
    return hiddenCount;
}

void IERenderable::fetchBufferDataAtIndex(const int index,
                                          QMap<QString, QVector2D>& vec2Data,
                                          QMap<QString, QVector3D>& vec3Data,
                                          QMap<QString, QVector4D>& vec4Data,
                                          QMap<QString, QMatrix4x4>& mat4Data)
{
    QMapIterator<QString, IEVertexBuffer<QVector2D>*> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext())
    {
        it1.next();
        if(!it1.value()->indexBoundsCheck(index))
            continue;
        vec2Data[it1.key()] = it1.value()->getBufferValue(index);
    }

    QMapIterator<QString, IEVertexBuffer<QVector3D>*> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext())
    {
        it2.next();
        if(!it2.value()->indexBoundsCheck(index))
            continue;
        vec3Data[it2.key()] = it2.value()->getBufferValue(index);
    }

    QMapIterator<QString, IEVertexBuffer<QVector4D>*> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext())
    {
        it3.next();
        if(!it3.value()->indexBoundsCheck(index))
            continue;
        vec4Data[it3.key()] = it3.value()->getBufferValue(index);
    }

    QMapIterator<QString, IEVertexBuffer<QMatrix4x4>*> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext())
    {
        it4.next();
        if(!it4.value()->indexBoundsCheck(index))
            continue;
        mat4Data[it4.key()] = it4.value()->getBufferValue(index);
    }
}

void IERenderable::appendVec2InstanceValue(const QString& key, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec3InstanceValue(const QString& key, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec4InstanceValue(const QString& key, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendMat4InstanceValue(const QString& key, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::removeVec2InstanceValue(const QString& key, const int index)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec3InstanceValue(const QString& key, const int index)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec4InstanceValue(const QString& key, const int index)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeMat4InstanceValue(const QString& key, const int index)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::setVec2InstanceValue(const QString& key, const int index, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec3InstanceValue(const QString& key, const int index, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec4InstanceValue(const QString& key, const int index, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->getValue(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::build(IEShader& shader)
{
    shader.bind();

    if(!this->isCreated())
        this->create();

    this->bind();

    indexBuffer->build();

    QMapIterator<QString, IEVertexBuffer<QVector2D>*> it2(vec2BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); it2.value()->build(shader.attributeLocation(it2.key())); }

    QMapIterator<QString, IEVertexBuffer<QVector3D>*> it3(vec3BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); it3.value()->build(shader.attributeLocation(it3.key())); }

    QMapIterator<QString, IEVertexBuffer<QVector4D>*> it4(vec4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); it4.value()->build(shader.attributeLocation(it4.key())); }

    QMapIterator<QString, IEVertexBuffer<QMatrix4x4>*> it5(mat4BufferContainer->getBuffers());
    while(it5.hasNext()) { it5.next(); it5.value()->build(shader.attributeLocation(it5.key())); }

    shader.release();
    this->release();
    indexBuffer->release();
    vec2BufferContainer->releaseAllBuffers();
    vec3BufferContainer->releaseAllBuffers();
    vec4BufferContainer->releaseAllBuffers();
    mat4BufferContainer->releaseAllBuffers();
}

void IERenderable::bindUniformData(IEShader& shader)
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

bool IERenderable::equals(const unsigned long long meshId,
                          const unsigned long long materialId,
                          const unsigned long long shaderId)
{
    return (this->meshId == meshId &&
            this->materialId == materialId &&
            this->shaderId == shaderId);
}

void IERenderable::purgeInstanceValues(const int index)
{
    QMapIterator<QString, IEVertexBuffer<QVector2D>*> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); removeVec2InstanceValue(it1.key(), index); }

    QMapIterator<QString, IEVertexBuffer<QVector3D>*> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); removeVec3InstanceValue(it2.key(), index); }

    QMapIterator<QString, IEVertexBuffer<QVector4D>*> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); removeVec4InstanceValue(it3.key(), index); }

    QMapIterator<QString, IEVertexBuffer<QMatrix4x4>*> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); removeMat4InstanceValue(it4.key(), index); }
}
