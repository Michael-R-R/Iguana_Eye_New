#include "IERenderable.h"
#include "IEShader.h"
#include "IEBufferObject.h"
#include "IERenderableFactory.h"
#include "IEBufferObjectFactory.h"
#include <stdexcept>

IERenderable::IERenderable(IERenderableType ieType, QObject* parent) :
    IEFileResource(parent),
    vao(new QOpenGLVertexArrayObject(this)),
    buffers(), dirtyAllocations(),
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
    vao(new QOpenGLVertexArrayObject(this)),
    buffers(), dirtyAllocations(),
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

bool IERenderable::draw(const QVector<std::any>& args)
{
    if(!vao)
        return false;

    bind();
    updateDirtyBuffers();

    return handleDraw(args);
}

bool IERenderable::bind()
{
    if(!vao)
        return false;

    vao->bind();

    return true;
}

bool IERenderable::release()
{
    if(!vao)
        return false;

    vao->release();

    return true;
}

bool IERenderable::addBuffer(const QString& name, IEBufferObject* buffer)
{
    if(!buffer)
        return false;

    buffer->setParent(this);

    buffers.insert(name, buffer);
    dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::removeBuffer(const QString& name)
{
    if(!doesBufferExist(name))
        return false;

    auto* buffer = buffers[name];
    buffers.remove(name);
    delete buffer;

    dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::appendBufferValue(const QString& name, const std::any& val)
{
    if(!doesBufferExist(name))
        return false;

    buffers[name]->appendValue(val);
    dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::removeBufferValue(const QString& name, const int index)
{
    if(doesBufferExist(name))
        return false;

    buffers[name]->removeValue(index);
    dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::setBufferValue(const QString& name, const int index, const std::any& val)
{
    if(!doesBufferExist(name))
        return false;

    buffers[name]->setValue(index, val);
    buffers[name]->handleSuballocate(index);

    return true;
}

bool IERenderable::setBufferValues(const QString& name, const std::any& val)
{
    if(!doesBufferExist(name))
        return false;

    buffers[name]->setValues(val);
    dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::build(IEShader& shader)
{
    if(!vao)
        return false;

    shader.bind();

    if(vao->isCreated())
        vao->destroy();

    vao->create();
    vao->bind();

    if(!handleBuild())
        return false;

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

    return true;
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

    out << renderable.type;

    int childCount = renderable.children.size();
    out << childCount;
    foreach(auto* child, renderable.children)
    {
        out << *child;
    }

    int renderableCount = renderable.renderables.size();
    out << renderableCount;
    foreach (auto* r, renderable.renderables)
    {
        out << *r;
    }

    int bufferCount = renderable.buffers.size();
    out << bufferCount;
    QHashIterator<QString, IEBufferObject*> it(renderable.buffers);
    while(it.hasNext())
    {
        it.next();
        auto* buffer = it.value();
        out << it.key() << buffer->getBufferType();
        out << *buffer;
    }

    out << renderable.primitiveMode << renderable.meshID
        << renderable.materialId << renderable.shaderId
        << renderable.dirtyAllocations;

    return out;
}

QDataStream& IERenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& renderable = static_cast<IERenderable&>(obj);
    renderable.buffers.clear();
    renderable.children.clear();
    renderable.renderables.clear();

    IERenderableType rType = IERenderableType::Unknown;
    in >> rType;

    int childSize = 0;
    in >> childSize;
    for(int i = 0; i < childSize; i++)
    {
        auto* r = IERenderableFactory::make(rType, &renderable);
        in >> *r;
        r->setParent(&renderable);
        renderable.children.append(r);
    }

    int renderableCount = 0;
    in >> renderableCount;
    for(int i = 0; i < renderableCount; i++)
    {
        auto* r = IERenderableFactory::make(rType, &renderable);
        in >> *r;
        r->setParent(&renderable);
        renderable.renderables.append(r);
    }

    int bufferCount = 0;
    in >> bufferCount;
    for(int i = 0; i < bufferCount; i++)
    {
        QString name = "";
        IEBufferType bType = IEBufferType::Unknown;
        in >> name >> bType;

        auto* buffer = IEBufferObjectFactory::make(bType, &renderable);
        in >> *buffer;

        renderable.buffers.insert(name, buffer);
    }

    in >> renderable.primitiveMode >> renderable.meshID
       >> renderable.materialId >> renderable.shaderId
       >> renderable.dirtyAllocations;

    return in;
}
