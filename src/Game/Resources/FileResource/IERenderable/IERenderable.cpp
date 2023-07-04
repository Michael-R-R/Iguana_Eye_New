#include "IERenderable.h"
#include "IEShader.h"
#include "IEBufferObject.h"
#include "IEBufferObjectFactory.h"
#include <stdexcept>

IERenderable::IERenderable(IERenderableType ieType, QObject* parent) :
    IEFileResource(parent),
    vao(), buffers(), dirtyAllocations(),
    type(ieType), primitiveMode(GL_TRIANGLES),
    materialId(0),
    shaderId(0)
{

}

IERenderable::IERenderable(IERenderableType ieType,
                           const QString& path,
                           const uint64_t meID,
                           const uint64_t maID,
                           const uint64_t sID,
                           QObject* parent) :
    IEFileResource(path, parent),
    vao(), buffers(), dirtyAllocations(),
    type(ieType), primitiveMode(GL_TRIANGLES),
    meshID(meID), materialId(maID), shaderId(sID)
{

}

IERenderable::~IERenderable()
{
    foreach(auto* child, children)
    {
        child->cleanup();
        delete child;
        child = nullptr;
    }

    foreach(auto* renderable, renderables)
    {
        renderable->cleanup();
        delete renderable;
        renderable = nullptr;
    }
}

void IERenderable::draw(const QVector<std::any>& args)
{
    bind();
    updateDirtyBuffers();
    handleDraw(args);
}

void IERenderable::bind()
{
    if(!vao)
        return;

    vao->bind();
}

void IERenderable::release()
{
    if(!vao)
        return;

    vao->release();
}

void IERenderable::init()
{
    vao = new QOpenGLVertexArrayObject(this);
}

void IERenderable::addBuffer(const QString& name, IEBufferObject* buffer)
{
    if(!buffer)
        throw std::exception("IERenderable::addBuffer()::null_buffer");

    buffer->setParent(this);

    buffers.insert(name, buffer);
    dirtyAllocations.insert(name);
}

void IERenderable::removeBuffer(const QString& name)
{
    if(!doesBufferExist(name))
        return;

    auto* buffer = buffers[name];
    buffers.remove(name);
    delete buffer;

    dirtyAllocations.insert(name);
}

void IERenderable::appendBufferValue(const QString& name, const std::any& val)
{
    if(!doesBufferExist(name))
        return;

    buffers[name]->appendValue(val);
    dirtyAllocations.insert(name);
}

void IERenderable::removeBufferValue(const QString& name, const int index)
{
    if(doesBufferExist(name))
        return;

    buffers[name]->removeValue(index);
    dirtyAllocations.insert(name);
}

void IERenderable::setBufferValue(const QString& name, const int index, const std::any& val)
{
    if(!doesBufferExist(name))
        return;

    buffers[name]->setValue(index, val);
    buffers[name]->handleSuballocate(index);
}

void IERenderable::setBufferValues(const QString& name, const std::any& val)
{
    if(!doesBufferExist(name))
        return;

    buffers[name]->setValues(val);
    dirtyAllocations.insert(name);
}

void IERenderable::build(IEShader& shader)
{
    shader.bind();

    if(vao->isCreated())
        vao->destroy();

    vao->create();
    vao->bind();

    handleBuild();

    QHashIterator<QString, IEBufferObject*> it(buffers);
    while(it.hasNext())
    {
        it.next();
        it.value()->build(shader.attributeLocation(it.key()));
    }

    vao->release();
    handleBuildRelease();
    foreach(auto* i, buffers)
    {
        i->release();
    }

    dirtyAllocations.clear();
}

void IERenderable::updateDirtyBuffers()
{
    foreach(auto& name, dirtyAllocations)
    {
        if(!doesBufferExist(name))
            continue;

        buffers[name]->handleAllocate(true);
    }

    dirtyAllocations.clear();
}

void IERenderable::cleanup()
{
    if(vao)
    {
        vao->destroy();
        delete vao;
        vao = nullptr;
    }

    foreach (auto* buffer, buffers)
    {
        buffer->destroy();
        delete buffer;
        buffer = nullptr;
    }

    buffers.clear();
    dirtyAllocations.clear();
}

bool IERenderable::doesBufferExist(const QString& name)
{
    return buffers.contains(name);
}

IEBufferObject* IERenderable::getBuffer(const QString& name)
{
    if(!doesBufferExist(name))
        return nullptr;

    return buffers[name];
}

QDataStream& IERenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& renderable = static_cast<const IERenderable&>(obj);

    // TODO implement

    return out;
}

QDataStream& IERenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& renderable = static_cast<IERenderable&>(obj);

    // TODO implement

    return in;
}
