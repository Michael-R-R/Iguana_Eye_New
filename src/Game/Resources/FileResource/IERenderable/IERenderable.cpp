#include "IERenderable.h"
#include "IEBufferObject.h"
#include "IEVertexBufferObject.h"
#include "IEShader.h"
#include <stdexcept>

IERenderable::IERenderable(QObject* parent) :
    IEFileResource(parent),
    VAOs(), buffers(), dirtyAllocations(),
    primitiveMode(GL_TRIANGLES),
    materialId(0),
    shaderId(0),
    uData()
{

}

IERenderable::IERenderable(const QString& path,
                           const uint64_t mID,
                           const uint64_t sID,
                           QObject* parent) :
    IEFileResource(path, parent),
    VAOs(), buffers(), dirtyAllocations(),
    primitiveMode(GL_TRIANGLES),
    materialId(mID),
    shaderId(sID),
    uData()
{

}

IERenderable::~IERenderable()
{
    cleanup();
}

void IERenderable::draw(const int index)
{
    bind(index);
    updateDirtyBuffers(index);
    handleDraw(index);
}

void IERenderable::bind(const int index)
{
    if(index < 0 || index >= VAOs.size())
        throw std::exception("IERenderable::bind()::Index_out_of_bounds");

    VAOs[index]->bind();
}

void IERenderable::bindData(IEShader& shader)
{
    uData.bind(shader);
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
        if(buffers[i].remove(name))
            dirtyAllocations[i].insert(name);
    }
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
            it.value()->build(shader.attributeLocation(it.key()));
        }

        vao->release();
        handleBuildRelease(i);
        foreach (auto* j, buffers[i])
        {
            j->release();
        }

        dirtyAllocations.clear();
    }
}

void IERenderable::updateDirtyBuffers(const int index)
{
    if(index < 0 || index >= buffers.size())
        throw std::exception("IERenderable::updateDirtyBuffers()::Index_out_of_bounds");

    foreach(auto& set, dirtyAllocations)
    {

    }
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
            auto* buffer = it.value();

            out << it.key() << buffer->getBufferType() << *buffer;

            it.next();
        }
    }

    out << renderable.dirtyAllocations
        << renderable.primitiveMode
        << renderable.materialId
        << renderable.shaderId
        << renderable.uData;

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

            IEBufferObject* buffer = nullptr;
            switch(type)
            {
            case IEBufferType::Vec2: { buffer = new IEVertexBufferObject<QVector2D>(&renderable); break; }
            case IEBufferType::Vec3: { buffer = new IEVertexBufferObject<QVector3D>(&renderable); break;  }
            case IEBufferType::Vec4: { buffer = new IEVertexBufferObject<QVector4D>(&renderable); break;  }
            case IEBufferType::Mat4: { buffer = new IEVertexBufferObject<QMatrix4x4>(&renderable); break;  }
            }

            in >> *buffer;

            result.insert(name, buffer);
        }

        renderable.buffers.append(result);
    }

    in >> renderable.dirtyAllocations
       >> renderable.primitiveMode
       >> renderable.materialId
       >> renderable.shaderId
       >> renderable.uData;

    return in;
}
