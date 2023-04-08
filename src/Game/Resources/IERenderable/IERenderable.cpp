#include "IERenderable.h"
#include "IEShader.h"

IERenderable::IERenderable() :
    QOpenGLVertexArrayObject(),
    IEResource(),
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(0), materialId(0), shaderId(0),
    indexBuffer(std::make_unique<IEIndexBuffer>()),
    vec2BufferContainer(std::make_unique<IEVertexBufferContainer<QVector2D>>()),
    vec3BufferContainer(std::make_unique<IEVertexBufferContainer<QVector3D>>()),
    vec4BufferContainer(std::make_unique<IEVertexBufferContainer<QVector4D>>()),
    mat4BufferContainer(std::make_unique<IEVertexBufferContainer<QMatrix4x4>>()),
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
    renderType(RenderType::None), drawMode(GL_TRIANGLES),
    meshId(meshId_), materialId(materialId_), shaderId(shaderId_),
    indexBuffer(std::make_unique<IEIndexBuffer>()),
    vec2BufferContainer(std::make_unique<IEVertexBufferContainer<QVector2D>>()),
    vec3BufferContainer(std::make_unique<IEVertexBufferContainer<QVector3D>>()),
    vec4BufferContainer(std::make_unique<IEVertexBufferContainer<QVector4D>>()),
    mat4BufferContainer(std::make_unique<IEVertexBufferContainer<QMatrix4x4>>()),
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

void IERenderable::addIndexBuffer(std::unique_ptr<IEIndexBuffer> buffer)
{
    indexBuffer = std::move(buffer);
}

void IERenderable::addVec2Buffer(const QString& key, std::unique_ptr<IEVertexBuffer<QVector2D>> value)
{
    vec2BufferContainer->add(key, std::move(value));
    dirtyVec2Buffers.insert(key);
}

void IERenderable::addVec3Buffer(const QString& key, std::unique_ptr<IEVertexBuffer<QVector3D>> value)
{
    vec3BufferContainer->add(key, std::move(value));
    dirtyVec3Buffers.insert(key);
}

void IERenderable::addVec4Buffer(const QString& key, std::unique_ptr<IEVertexBuffer<QVector4D>> value)
{
    vec4BufferContainer->add(key, std::move(value));
    dirtyVec4Buffers.insert(key);
}

void IERenderable::addMat4Buffer(const QString& key, std::unique_ptr<IEVertexBuffer<QMatrix4x4>> value)
{
    mat4BufferContainer->add(key, std::move(value));
    dirtyMat4Buffers.insert(key);
}

void IERenderable::setVec2BufferData(const QString& key, const QVector<QVector2D>& data)
{
    auto* buffer = vec2BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec2Buffers.insert(key);
}

void IERenderable::setVec3BufferData(const QString& key, const QVector<QVector3D>& data)
{
    auto* buffer = vec3BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec3Buffers.insert(key);
}

void IERenderable::setVec4BufferData(const QString& key, const QVector<QVector4D>& data)
{
    auto* buffer = vec4BufferContainer->value(key);
    if(!buffer)
        return;

    buffer->setBufferData(data);
    dirtyVec4Buffers.insert(key);
}

void IERenderable::setMat4BufferData(const QString& key, const QVector<QMatrix4x4>& data)
{
    auto* buffer = mat4BufferContainer->value(key);
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
    for(auto& i : *vec2BufferContainer->getBuffers())
    {
        auto& key = i.first;
        auto& buffer = *i.second;
        if(!buffer.indexBoundsCheck(index))
            continue;
        vec2Data[key] = buffer.getBufferValue(index);
    }

    for(auto& i : *vec3BufferContainer->getBuffers())
    {
        auto& key = i.first;
        auto& buffer = *i.second;
        if(!buffer.indexBoundsCheck(index))
            continue;
        vec3Data[key] = buffer.getBufferValue(index);
    }

    for(auto& i : *vec4BufferContainer->getBuffers())
    {
        auto& key = i.first;
        auto& buffer = *i.second;
        if(!buffer.indexBoundsCheck(index))
            continue;
        vec4Data[key] = buffer.getBufferValue(index);
    }

    for(auto& i : *mat4BufferContainer->getBuffers())
    {
        auto& key = i.first;
        auto& buffer = *i.second;
        if(!buffer.indexBoundsCheck(index))
            continue;
        mat4Data[key] = buffer.getBufferValue(index);
    }
}

void IERenderable::appendVec2InstanceValue(const QString& key, const QVector2D& value)
{
    auto* buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec3InstanceValue(const QString& key, const QVector3D& value)
{
    auto* buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendVec4InstanceValue(const QString& key, const QVector4D& value)
{
    auto* buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::appendMat4InstanceValue(const QString& key, const QMatrix4x4& value)
{
    auto* buffer = mat4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->appendBufferValue(value);
}

void IERenderable::removeVec2InstanceValue(const QString& key, const int index)
{
    auto* buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec2Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec3InstanceValue(const QString& key, const int index)
{
    auto* buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec3Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeVec4InstanceValue(const QString& key, const int index)
{
    auto* buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyVec4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::removeMat4InstanceValue(const QString& key, const int index)
{
    auto* buffer = mat4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    dirtyMat4Buffers.insert(key);

    buffer->removeBufferValue(index);
}

void IERenderable::setVec2InstanceValue(const QString& key, const int index, const QVector2D& value)
{
    auto* buffer = vec2BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec3InstanceValue(const QString& key, const int index, const QVector3D& value)
{
    auto* buffer = vec3BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setVec4InstanceValue(const QString& key, const int index, const QVector4D& value)
{
    auto* buffer = vec4BufferContainer->value(key);
    if(!buffer || !buffer->getIsInstanced())
        return;

    buffer->setBufferValue(index, value);
    buffer->subAllocate(index);
}

void IERenderable::setMat4InstanceValue(const QString& key, const int index, const QMatrix4x4& value)
{
    auto* buffer = mat4BufferContainer->value(key);
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
    for(auto& i : *vec2BufferContainer->getBuffers()) { i.second->build(shader.attributeLocation(i.first)); }
    for(auto& i : *vec3BufferContainer->getBuffers()) { i.second->build(shader.attributeLocation(i.first)); }
    for(auto& i : *vec4BufferContainer->getBuffers()) { i.second->build(shader.attributeLocation(i.first)); }
    for(auto& i : *mat4BufferContainer->getBuffers()) { i.second->build(shader.attributeLocation(i.first)); }

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

void IERenderable::purgeInstanceValues(const int index)
{
    for(auto& i : *vec2BufferContainer->getBuffers()) { removeVec2InstanceValue(i.first, index); }
    for(auto& i : *vec3BufferContainer->getBuffers()) { removeVec3InstanceValue(i.first, index); }
    for(auto& i : *vec4BufferContainer->getBuffers()) { removeVec4InstanceValue(i.first, index); }
    for(auto& i : *mat4BufferContainer->getBuffers()) { removeMat4InstanceValue(i.first, index); }
}

QDataStream& IERenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEResource::serialize(out, obj);

    const auto& renderable = static_cast<const IERenderable&>(obj);

    out << renderable.renderType
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

    in >> renderable.renderType
       >> renderable.drawMode >> renderable.meshId
       >> renderable.materialId >> renderable.shaderId
       >> *renderable.indexBuffer >> *renderable.vec2BufferContainer
       >> *renderable.vec3BufferContainer >> *renderable.vec4BufferContainer
       >> *renderable.mat4BufferContainer >> renderable.shownCount
       >> renderable.hiddenCount >> renderable.uniformData;

    return in;
}
