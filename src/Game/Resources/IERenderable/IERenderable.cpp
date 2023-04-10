#include "IERenderable.h"
#include "IEShader.h"

IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(),
    IEResource(),
    renderMode(RenderMode::None), drawMode(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    indexBuffer(QSharedPointer<IEIndexBuffer>::create()),
    vec2BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector2D>>::create()),
    vec3BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector3D>>::create()),
    vec4BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector4D>>::create()),
    mat4BufferContainer(QSharedPointer<IEVertexBufferContainer<QMatrix4x4>>::create()),
    shownCount(0), hiddenCount(0),
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers()
{

}

IERenderable::IERenderable(const QString& path,
                           const unsigned long long meshId_,
                           const unsigned long long materialId_,
                           const unsigned long long shaderId_) :
    QOpenGLVertexArrayObject(),
    IEResource(path),
    renderMode(RenderMode::None), drawMode(GL_TRIANGLES),
    meshId(meshId_), materialId(materialId_), shaderId(shaderId_),
    indexBuffer(QSharedPointer<IEIndexBuffer>::create()),
    vec2BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector2D>>::create()),
    vec3BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector3D>>::create()),
    vec4BufferContainer(QSharedPointer<IEVertexBufferContainer<QVector4D>>::create()),
    mat4BufferContainer(QSharedPointer<IEVertexBufferContainer<QMatrix4x4>>::create()),
    shownCount(0), hiddenCount(0),
    uniformData(),
    dirtyVec2Buffers(), dirtyVec3Buffers(),
    dirtyVec4Buffers(), dirtyMat4Buffers()
{

}

IERenderable::~IERenderable()
{
    if(this->isCreated())
        this->destroy();
}

void IERenderable::addIndexBuffer(QSharedPointer<IEIndexBuffer> buffer)
{
    indexBuffer = buffer;
}

void IERenderable::addVec2Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector2D>> value)
{
    vec2BufferContainer->add(key, value);
    dirtyVec2Buffers.insert(key);
}

void IERenderable::addVec3Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector3D>> value)
{
    vec3BufferContainer->add(key, value);
    dirtyVec3Buffers.insert(key);
}

void IERenderable::addVec4Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QVector4D>> value)
{
    vec4BufferContainer->add(key, value);
    dirtyVec4Buffers.insert(key);
}

void IERenderable::addMat4Buffer(const QString& key, QSharedPointer<IEVertexBuffer<QMatrix4x4>> value)
{
    mat4BufferContainer->add(key, value);
    dirtyMat4Buffers.insert(key);
}

void IERenderable::setVec2BufferData(const QString& key, const QVector<QVector2D>& data)
{
    auto buffer = vec2BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec2Buffers.insert(key);
}

void IERenderable::setVec3BufferData(const QString& key, const QVector<QVector3D>& data)
{
    auto buffer = vec3BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec3Buffers.insert(key);
}

void IERenderable::setVec4BufferData(const QString& key, const QVector<QVector4D>& data)
{
    auto buffer = vec4BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec4Buffers.insert(key);
}

void IERenderable::setMat4BufferData(const QString& key, const QVector<QMatrix4x4>& data)
{
    auto buffer = mat4BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyMat4Buffers.insert(key);
}

int IERenderable::addShownInstance()
{
    appendInstanceValues();

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
    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector2D>>> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext())
    {
        it1.next();
        auto key = it1.key();
        auto buffer = it1.value();
        if(!buffer->indexBoundsCheck(index))
            continue;
        vec2Data[key] = buffer->getBufferValue(index);
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector3D>>> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext())
    {
        it2.next();
        auto key = it2.key();
        auto buffer = it2.value();
        if(!buffer->indexBoundsCheck(index))
            continue;
        vec3Data[key] = buffer->getBufferValue(index);
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector4D>>> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext())
    {
        it3.next();
        auto key = it3.key();
        auto buffer = it3.value();
        if(!buffer->indexBoundsCheck(index))
            continue;
        vec4Data[key] = buffer->getBufferValue(index);
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QMatrix4x4>>> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext())
    {
        it4.next();
        auto key = it4.key();
        auto buffer = it4.value();
        if(!buffer->indexBoundsCheck(index))
            continue;
        mat4Data[key] = buffer->getBufferValue(index);
    }
}

void IERenderable::appendVec2InstanceValue(const QString& key, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec3InstanceValue(const QString& key, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec4InstanceValue(const QString& key, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendMat4InstanceValue(const QString& key, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::removeVec2InstanceValue(const QString& key, const int index)
{
    auto buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec3InstanceValue(const QString& key, const int index)
{
    auto buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec4InstanceValue(const QString& key, const int index)
{
    auto buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeMat4InstanceValue(const QString& key, const int index)
{
    auto buffer = mat4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::setVec2InstanceValue(const QString& key, const int index, const QVector2D& value)
{
    auto buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec3InstanceValue(const QString& key, const int index, const QVector3D& value)
{
    auto buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec4InstanceValue(const QString& key, const int index, const QVector4D& value)
{
    auto buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value)
{
    auto buffer = mat4BufferContainer->value(key);
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

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector2D>>> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); it1.value()->build(shader.attributeLocation(it1.key())); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector3D>>> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); it2.value()->build(shader.attributeLocation(it2.key())); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector4D>>> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); it3.value()->build(shader.attributeLocation(it3.key())); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QMatrix4x4>>> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); it4.value()->build(shader.attributeLocation(it4.key())); }

    shader.release();
    this->release();
    indexBuffer->release();
    vec2BufferContainer->releaseAllBuffers();
    vec3BufferContainer->releaseAllBuffers();
    vec4BufferContainer->releaseAllBuffers();
    mat4BufferContainer->releaseAllBuffers();

    dirtyVec2Buffers.clear();
    dirtyVec3Buffers.clear();
    dirtyVec4Buffers.clear();
    dirtyMat4Buffers.clear();
}

void IERenderable::bindUniformData(IEShader& shader)
{
    uniformData.bind(shader);
}

void IERenderable::checkForDirtyBuffers()
{
    foreach(auto& key, dirtyVec2Buffers)
        vec2BufferContainer->value(key)->reallocate();
    dirtyVec2Buffers.clear();

    foreach(auto& key, dirtyVec3Buffers)
        vec3BufferContainer->value(key)->reallocate();
    dirtyVec3Buffers.clear();

    foreach(auto& key, dirtyVec4Buffers)
        vec4BufferContainer->value(key)->reallocate();
    dirtyVec4Buffers.clear();

    foreach(auto& key, dirtyMat4Buffers)
        mat4BufferContainer->value(key)->reallocate();
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

void IERenderable::appendInstanceValues()
{
    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector2D>>> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext())
    {
        it1.next();
        if(!it1.value()->getIsInstanced())
            continue;
        it1.value()->appendBufferValue(QVector2D());
        dirtyVec2Buffers.insert(it1.key());
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector3D>>> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext())
    {
        it2.next();
        if(!it2.value()->getIsInstanced())
            continue;
        it2.value()->appendBufferValue(QVector3D());
        dirtyVec3Buffers.insert(it2.key());
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector4D>>> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext())
    {
        it3.next();
        if(!it3.value()->getIsInstanced())
            continue;
        it3.value()->appendBufferValue(QVector4D());
        dirtyVec4Buffers.insert(it3.key());
    }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QMatrix4x4>>> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext())
    {
        it4.next();
        if(!it4.value()->getIsInstanced())
            continue;
        it4.value()->appendBufferValue(QMatrix4x4());
        dirtyMat4Buffers.insert(it4.key());
    }
}

void IERenderable::purgeInstanceValues(const int index)
{
    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector2D>>> it1(vec2BufferContainer->getBuffers());
    while(it1.hasNext()) { it1.next(); removeVec2InstanceValue(it1.key(), index); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector3D>>> it2(vec3BufferContainer->getBuffers());
    while(it2.hasNext()) { it2.next(); removeVec3InstanceValue(it2.key(), index); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QVector4D>>> it3(vec4BufferContainer->getBuffers());
    while(it3.hasNext()) { it3.next(); removeVec4InstanceValue(it3.key(), index); }

    QMapIterator<QString, QSharedPointer<IEVertexBuffer<QMatrix4x4>>> it4(mat4BufferContainer->getBuffers());
    while(it4.hasNext()) { it4.next(); removeMat4InstanceValue(it4.key(), index); }
}

QDataStream& IERenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEResource::serialize(out, obj);

    const auto& renderable = static_cast<const IERenderable&>(obj);

    out << renderable.renderMode
        << renderable.drawMode << renderable.meshId
        << renderable.materialId << renderable.shaderId
        << *renderable.indexBuffer << *renderable.vec2BufferContainer
        << *renderable.vec3BufferContainer << *renderable.vec4BufferContainer
        << *renderable.mat4BufferContainer << renderable.shownCount
        << renderable.hiddenCount << renderable.uniformData;

    return out;
}

QDataStream& IERenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource::deserialize(in, obj);

    auto& renderable = static_cast<IERenderable&>(obj);

    in >> renderable.renderMode
       >> renderable.drawMode >> renderable.meshId
       >> renderable.materialId >> renderable.shaderId
       >> *renderable.indexBuffer >> *renderable.vec2BufferContainer
       >> *renderable.vec3BufferContainer >> *renderable.vec4BufferContainer
       >> *renderable.mat4BufferContainer >> renderable.shownCount
       >> renderable.hiddenCount >> renderable.uniformData;

    return in;
}
