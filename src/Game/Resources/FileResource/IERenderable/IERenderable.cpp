#include "IERenderable.h"
#include "IEShader.h"
#include "IEBufferObject.h"
#include "IEBufferObjectFactory.h"
#include <stdexcept>

IERenderable::IERenderable(IERenderableType ieType, QObject* parent) :
    IEFileResource(parent),
    VAOs(), buffers(), dirtyAllocations(),
    type(ieType), primitiveMode(GL_TRIANGLES),
    materialId(0),
    shaderId(0)
{

}

IERenderable::IERenderable(IERenderableType ieType,
                           const QString& path,
                           const uint64_t mID,
                           const uint64_t sID,
                           QObject* parent) :
    IEFileResource(path, parent),
    VAOs(), buffers(), dirtyAllocations(),
    type(ieType), primitiveMode(GL_TRIANGLES),
    materialId(mID),
    shaderId(sID)
{

}

IERenderable::~IERenderable()
{
    cleanup();
}

void IERenderable::draw(const int index, const QVector<std::any>& args)
{
    bind(index);
    updateDirtyBuffers(index);
    handleDraw(index, args);
}

void IERenderable::bind(const int index)
{
    if(index < 0 || index >= VAOs.size())
        throw std::exception("IERenderable::bind()::Index_out_of_bounds");

    VAOs[index]->bind();
}

void IERenderable::release(const int index)
{
    if(index < 0 || index >= VAOs.size())
        throw std::exception("IERenderable::release()::Index_out_of_bounds");

    VAOs[index]->release();
}

int IERenderable::addVAO()
{
    const int index = VAOs.size();

    VAOs.append(new QOpenGLVertexArrayObject(this));
    buffers.append(QHash<QString, IEBufferObject*>());
    dirtyAllocations.append(QSet<QString>());

    return index;
}

void IERenderable::addBuffer(const int index, const QString& name, IEBufferObject* buffer)
{
    if(index < 0 || index >= VAOs.size())
        throw std::exception("IERenderable::addBuffer()::Index_out_of_bounds");

    if(!buffer)
        throw std::exception("IERenderable::addBuffer()::null_buffer");

    buffers[index].insert(name, buffer);
    dirtyAllocations[index].insert(name);
}

void IERenderable::removeBuffer(const QString& name)
{
    for(int i = 0; i < VAOs.size(); i++)
    {
        if(!doesBufferExist(i, name))
            continue;

        auto* buffer = buffers[i][name];
        buffers[i].remove(name);
        delete buffer;

        dirtyAllocations[i].insert(name);
    }
}

void IERenderable::addBufferValue(const QString& name, const std::any& val, int index)
{
    if(index < 0 || index >= buffers.size())
        return;

    if(doesBufferExist(index, name))
    {
        buffers[index][name]->appendValue(val);
    }

    addBufferValue(name, val, ++index);
}

void IERenderable::removeBufferValue(const QString& name, const int bufferIndex, int index)
{
    if(index < 0 || index >= buffers.size())
        return;

    if(doesBufferExist(index, name))
    {
        buffers[index][name]->removeValue(bufferIndex);
    }

    removeBufferValue(name, bufferIndex, ++index);
}

void IERenderable::setBufferValue(const QString& name, const int bufferIndex, const std::any& val, int index)
{
    if(index < 0 || index >= buffers.size())
        return;

    if(doesBufferExist(index, name))
    {
        buffers[index][name]->setValue(bufferIndex, val);
        buffers[index][name]->handleSuballocate(bufferIndex);
    }

    setBufferValue(name, bufferIndex, val, ++index);
}

void IERenderable::setBufferValues(const QString& name, const std::any& val, int index)
{
    if(index < 0 || index >= buffers.size())
        return;

    if(doesBufferExist(index, name))
    {
        buffers[index][name]->setValues(val);
        dirtyAllocations[index].insert(name);
    }

    setBufferValues(name, val, ++index);
}

void IERenderable::build(IEShader& shader)
{
    for(int i = 0; i < VAOs.size(); i++)
    {
        auto* vao = VAOs[i];

        if(vao->isCreated())
            vao->destroy();

        vao->create();
        vao->bind();

        handleBuild(i);

        QHashIterator<QString, IEBufferObject*> it(buffers[i]);
        while(it.hasNext())
        {
            it.next();

            it.value()->build(shader.attributeLocation(it.key()));
        }

        vao->release();
        handleBuildRelease(i);
        foreach(auto* j, buffers[i])
        {
            j->release();
        }

        dirtyAllocations[i].clear();
    }
}

void IERenderable::updateDirtyBuffers(const int index)
{
    if(index < 0 || index >= buffers.size())
        throw std::exception("IERenderable::updateDirtyBuffers()::Index_out_of_bounds");

    foreach(auto& name, dirtyAllocations[index])
    {
        if(!doesBufferExist(index, name))
            continue;

        buffers[index][name]->handleAllocate(true);
    }

    dirtyAllocations[index].clear();
}

void IERenderable::cleanup()
{
    foreach (auto* i, VAOs)
    {
        i->destroy();
        delete i;
        i = nullptr;
    }

    foreach (auto& i, buffers)
    {
        foreach (auto* j, i)
        {
            j->destroy();
            delete j;
            j = nullptr;
        }
    }

    VAOs.clear();
    buffers.clear();
    dirtyAllocations.clear();
}

bool IERenderable::doesBufferExist(const int index, const QString& name)
{
    return buffers[index].contains(name);
}

IEBufferObject* IERenderable::getBuffer(const int index, const QString& name)
{
    if(!doesBufferExist(index, name))
        return nullptr;

    return buffers[index][name];
}

QDataStream& IERenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& renderable = static_cast<const IERenderable&>(obj);

    const int vaoSize = renderable.VAOs.size();
    out << vaoSize;

    const int bufferSize = renderable.buffers.size();
    out << bufferSize;
    foreach (auto& i, renderable.buffers)
    {
        out << i.size();

        QHashIterator<QString, IEBufferObject*> it(i);
        while(it.hasNext())
        {
            it.next();

            QString name = it.key();
            auto* buffer = it.value();

            out << name << buffer->getBufferType() << *buffer;
        }
    }

    out << renderable.dirtyAllocations
        << renderable.type
        << renderable.primitiveMode
        << renderable.materialId
        << renderable.shaderId;

    return out;
}

QDataStream& IERenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& renderable = static_cast<IERenderable&>(obj);
    renderable.cleanup();

    int vaoSize = 0;
    in >> vaoSize;
    for(int i = 0; i < vaoSize; i++)
    {
        renderable.VAOs.append(new QOpenGLVertexArrayObject(&renderable));
    }

    int bufferSize = 0;
    in >> bufferSize;
    for(int i = 0; i < bufferSize; i++)
    {
        QHash<QString, IEBufferObject*> result;

        int tempSize = 0;
        in >> tempSize;
        for(int j = 0; j < tempSize; j++)
        {
            QString name = "";
            IEBufferType type = IEBufferType::Unknown;
            in >> name >> type;

            IEBufferObject* buffer = IEBufferObjectFactory::make(type, &renderable);
            if(!buffer)
                continue;

            in >> *buffer;

            result.insert(name, buffer);
        }

        renderable.buffers.append(result);
    }

    in >> renderable.dirtyAllocations
       >> renderable.type
       >> renderable.primitiveMode
       >> renderable.materialId
       >> renderable.shaderId;

    return in;
}
