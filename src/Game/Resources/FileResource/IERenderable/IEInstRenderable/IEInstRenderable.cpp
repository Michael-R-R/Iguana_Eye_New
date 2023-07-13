#include "IEInstRenderable.h"
#include "IEBufferObject.h"
#include "IESerializeConverter.h"

IEInstRenderable::IEInstRenderable(IERenderableType ieType, QObject* parent) :
    IERenderable(ieType, parent),
    instNodes(), shown(0), hidden(0)
{

}

IEInstRenderable::IEInstRenderable(IERenderableType ieType, const QString& path, QObject* parent) :
    IERenderable(ieType, path, parent),
    instNodes(), shown(0), hidden(0)
{

}

IEInstRenderable::IEInstRenderable(IERenderable* parent) :
    IERenderable(parent),
    instNodes(), shown(0), hidden(0)
{

}

IEInstRenderable::~IEInstRenderable()
{

}

int IEInstRenderable::appendNode(IERenderableNode* node)
{
    const int index = IERenderable::appendNode(node);
    if(index < 0) { return -1; }

    instNodes.append(new IEInstRenderableNode());

    return index;
}

bool IEInstRenderable::removeNode(const int index)
{
    if(!IERenderable::removeNode(index))
        return false;

    auto* temp = instNodes[index];
    instNodes.removeAt(index);
    delete temp;

    return true;
}

void IEInstRenderable::cleanup()
{
    IERenderable::cleanup();

    foreach(auto* i, instNodes)
    {
        delete i;
        i = nullptr;
    }

    instNodes.clear();
}

IEInstRenderableNode* IEInstRenderable::getInstNode(const int index)
{
    if(!indexBoundsCheck(index))
        return nullptr;

    return instNodes[index];
}

int IEInstRenderable::addShown()
{
    for(int i = 0; i < instNodes.size(); i++)
    {
        QHashIterator<QString, IEBufferObject*> it(nodes[i]->buffers);
        while(it.hasNext())
        {
            it.next();

            IEBufferObject* buffer = it.value();
            if(!buffer->getIsInstanced())
                continue;

            buffer->appendValue(std::any{});

            nodes[i]->dirtyAllocations.insert(it.key());
        }
    }

    return shown++;
}

int IEInstRenderable::addShownFromHidden(const int index)
{
    if(!hiddenIndexBoundsCheck(index))
        return -1;

    for(int i = 0; i < instNodes.size(); i++)
    {
        QHashIterator<QString, std::any> it(instNodes[i]->hiddenData[index]);
        while(it.hasNext())
        {
            it.next();

            if(!doesBufferExist(i, it.key()))
                continue;

            IEBufferObject* buffer = nodes[i]->buffers[it.key()];
            if(!buffer->getIsInstanced())
                continue;

            if(buffer->appendValue(it.value()) < 0)
                continue;

            nodes[i]->dirtyAllocations.insert(it.key());
        }
    }

    removeHidden(index);

    return shown++;
}

bool IEInstRenderable::removeShown(const int index)
{
    if(!shownIndexBoundsCheck(index))
        return false;

    for(int i = 0; i < instNodes.size(); i++)
    {
        QHashIterator<QString, IEBufferObject*> it(nodes[i]->buffers);
        while(it.hasNext())
        {
            it.next();

            IEBufferObject* buffer = it.value();
            if(!buffer->getIsInstanced())
                continue;

            if(!buffer->removeValue(index))
                continue;

            nodes[i]->dirtyAllocations.insert(it.key());
        }
    }

    shown--;

    return true;
}

int IEInstRenderable::addHiddenFromShown(const int index)
{
    if(!shownIndexBoundsCheck(index))
        return -1;

    for(int i = 0; i < instNodes.size(); i++)
    {
        instNodes[i]->hiddenData.append(getInstValues(i, index));
    }

    removeShown(index);

    return hidden++;
}

bool IEInstRenderable::removeHidden(const int index)
{
    if(!hiddenIndexBoundsCheck(index))
        return false;

    for(int i = 0; i < instNodes.size(); i++)
    {
        const int lastIndex = hidden - 1;

        instNodes[i]->hiddenData[index] = instNodes[i]->hiddenData[lastIndex];
        instNodes[i]->hiddenData.removeLast();
    }

    hidden--;

    return true;
}

QHash<QString, std::any> IEInstRenderable::getInstValues(const int index, const int shownIndex)
{
    if(!shownIndexBoundsCheck(shownIndex))
        return QHash<QString, std::any>{};

    QHash<QString, std::any> values;

    QHashIterator<QString, IEBufferObject*> it(nodes[index]->buffers);
    while(it.hasNext())
    {
        it.next();

        IEBufferObject* buffer = it.value();
        if(!buffer->getIsInstanced())
            continue;

        values.insert(it.key(), buffer->getValue(shownIndex));
    }

    return values;
}

QDataStream& IEInstRenderable::serialize(QDataStream& out, const IESerializable& obj) const
{
    IERenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstRenderable&>(obj);

    // TODO implement

    return out;
}

QDataStream& IEInstRenderable::deserialize(QDataStream& in, IESerializable& obj)
{
    IERenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstRenderable&>(obj);

    // TODO implement

    return in;
}

bool IEInstRenderable::shownIndexBoundsCheck(const int index)
{
    return (index > -1 && index < shown);
}

bool IEInstRenderable::hiddenIndexBoundsCheck(const int index)
{
    return (index > -1 && index < hidden);
}

bool IEInstRenderable::indexBoundsCheck(const int index)
{
    return (index > -1 && index < instNodes.size());
}
