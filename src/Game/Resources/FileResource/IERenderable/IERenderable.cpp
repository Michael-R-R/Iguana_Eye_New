#include "IERenderable.h"
#include "IEShader.h"
#include "IERenderableFactory.h"
#include <stdexcept>

IERenderable::IERenderable(IERenderableType ieType, QObject* parent) :
    IEFileResource(parent),
    nodes(),
    meshID(0),
    materialID(0),
    shaderID(0),
    type(ieType)
{

}

IERenderable::IERenderable(IERenderableType ieType, const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    nodes(),
    meshID(0),
    materialID(0),
    shaderID(0),
    type(ieType)
{

}

IERenderable::IERenderable(IERenderable* parent) :
    IEFileResource(parent->getName(), parent),
    nodes(),
    meshID(parent->getMeshID()),
    materialID(parent->getMaterialID()),
    shaderID(parent->getShaderID()),
    type(parent->getType())
{

}

IERenderable::~IERenderable()
{
    IERenderable::cleanup();
}

void IERenderable::draw(const int index, const QVector<std::any>& args)
{
    updateDirtyBuffers(index);
    handleDraw(index, args);
}

int IERenderable::appendNode(IERenderableNode* node)
{
    if(!node) { return -1; }

    const int index = nodes.size();

    nodes.append(node);

    return index;
}

bool IERenderable::removeNode(const int index)
{
    if(!indexBoundsCheck(index))
        return false;

    auto* temp = nodes[index];
    nodes.removeAt(index);
    delete temp;

    return true;
}

void IERenderable::cleanup()
{
    foreach(auto* i, nodes)
    {
        delete i;
        i = nullptr;
    }

    nodes.clear();
}

IERenderableNode* IERenderable::getNode(const int index)
{
    if(!indexBoundsCheck(index))
        return nullptr;

    return nodes[index];
}

bool IERenderable::addBuffer(const int index,
                             const QString& name,
                             const IEBufferType type,
                             const int s, const int o, const int d)
{
    if(!indexBoundsCheck(index))
        return false;

    if(type == IEBufferType::Unknown)
        return false;

    IEBufferObject* buffer = IEBufferObjectFactory::make(type, s, o, d, this);

    nodes[index]->buffers.insert(name, buffer);
    nodes[index]->dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::removeBuffer(const int index, const QString& name)
{
    if(!doesBufferExist(index, name))
        return false;

    auto* buffer = nodes[index]->buffers[name];
    nodes[index]->buffers.remove(name);
    delete buffer;

    nodes[index]->dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::appendBufferValue(const int index, const QString& name, const std::any& val)
{
    if(!doesBufferExist(index, name))
        return false;

    nodes[index]->buffers[name]->appendValue(val);
    nodes[index]->dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::removeBufferValue(const int index, const QString& name, const int bufferIndex)
{
    if(!doesBufferExist(index, name))
        return false;

    nodes[index]->buffers[name]->removeValue(bufferIndex);
    nodes[index]->dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::setBufferValue(const int index, const QString& name, const int bufferIndex, const std::any& val)
{
    if(!doesBufferExist(index, name))
        return false;

    nodes[index]->buffers[name]->setValue(bufferIndex, val);
    nodes[index]->buffers[name]->handleSuballocate(bufferIndex);

    return true;
}

bool IERenderable::setBufferValues(const int index, const QString& name, const std::any& val)
{
    if(!doesBufferExist(index, name))
        return false;

    nodes[index]->buffers[name]->setValues(val);
    nodes[index]->dirtyAllocations.insert(name);

    return true;
}

bool IERenderable::doesBufferExist(const int index, const QString& name)
{
    if(!indexBoundsCheck(index))
        return false;

    return nodes[index]->buffers.contains(name);
}

void IERenderable::updateDirtyBuffers(const int index)
{
    if(!indexBoundsCheck(index))
        return;

    foreach(auto& name, nodes[index]->dirtyAllocations)
    {
        if(!doesBufferExist(index, name))
            continue;

        nodes[index]->buffers[name]->handleAllocate(true);
    }

    nodes[index]->dirtyAllocations.clear();
}

IEBufferObject* IERenderable::getBuffer(const int index, const QString& name)
{
    if(!doesBufferExist(index, name))
        return nullptr;

    return nodes[index]->buffers[name];
}

bool IERenderable::build(const int index, IEShader& shader)
{
    if(!indexBoundsCheck(index))
        return false;

    shader.bind();

    IERenderableNode* node = nodes[index];

    if(node->VAO->isCreated())
        node->VAO->destroy();

    node->VAO->create();
    node->VAO->bind();

    if(!handleBuild(index))
    {
        node->VAO->destroy();
        return false;
    }

    QHashIterator<QString, IEBufferObject*> it(node->buffers);
    while(it.hasNext())
    {
        it.next();

        auto* buffer = it.value();
        const int loc = shader.attributeLocation(it.key());
        buffer->build(loc);
    }

    node->VAO->release();
    handleBuildRelease(index);
    foreach(auto* i, node->buffers)
    {
        i->release();
    }

    node->dirtyAllocations.clear();

    return true;
}

QDataStream& IERenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& renderable = static_cast<const IERenderable&>(obj);

    out << (int)renderable.nodes.size();
    foreach(auto* i, renderable.nodes)
    {
        out << *i;
    }

    out << renderable.meshID
        << renderable.materialID
        << renderable.shaderID
        << renderable.type;

    return out;
}

QDataStream& IERenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& renderable = static_cast<IERenderable&>(obj);
    renderable.cleanup();

    int nodeCount = 0;
    in >> nodeCount;
    for(int i = 0; i < nodeCount; i++)
    {
        auto* node = new IERenderableNode();
        in >> *node;
        renderable.nodes.append(node);
    }

    in >> renderable.meshID
       >> renderable.materialID
       >> renderable.shaderID
       >> renderable.type;

    return in;
}

bool IERenderable::indexBoundsCheck(const int index)
{
    return (index > -1 && index < nodes.size());
}
