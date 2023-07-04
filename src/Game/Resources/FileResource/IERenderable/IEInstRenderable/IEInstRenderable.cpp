#include "IEInstRenderable.h"
#include "IEBufferObject.h"

IEInstRenderable::IEInstRenderable(IERenderableType ieType, QObject* parent) :
    IERenderable(ieType, parent),
    hiddenData(),
    shown(0), hidden(0)
{

}

IEInstRenderable::IEInstRenderable(IERenderableType ieType,
                                   const QString& path,
                                   const uint64_t meID,
                                   const uint64_t maID,
                                   const uint64_t sID,
                                   QObject* parent) :
    IERenderable(ieType, path, meID, maID, sID, parent),
    hiddenData(),
    shown(0), hidden(0)
{

}

IEInstRenderable::~IEInstRenderable()
{

}

int IEInstRenderable::addShown()
{
    QHashIterator<QString, IEBufferObject*> it(buffers);
    while(it.hasNext())
    {
        it.next();

        auto* buffer = it.value();
        if(!buffer->getIsInstanced())
            continue;

        if(buffer->appendValue(std::any{}) < 0)
            continue;

        dirtyAllocations.insert(it.key());
    }

    return shown++;
}

int IEInstRenderable::addShown(const int hiddenIndex)
{
    if(!hiddenIndexBoundsCheck(hiddenIndex))
        return -1;

    QHashIterator<QString, std::any> it(hiddenData[hiddenIndex]);
    while(it.hasNext())
    {
        it.next();

        if(!doesBufferExist(it.key()))
            continue;

        auto* buffer = buffers[it.key()];
        if(!buffer->getIsInstanced())
            continue;

        if(buffer->appendValue(it.value()) > -1)
            dirtyAllocations.insert(it.key());
    }

    removeHidden(hiddenIndex);

    return shown++;
}

bool IEInstRenderable::removeShown(const int index)
{
    if(!shownIndexBoundsCheck(index))
        return false;

    QHashIterator<QString, IEBufferObject*> it(buffers);
    while(it.hasNext())
    {
        it.next();

        auto* buffer = it.value();
        if(!buffer->getIsInstanced())
            continue;

        if(buffer->removeValue(index))
            dirtyAllocations.insert(it.key());
    }

    shown--;

    return true;
}

int IEInstRenderable::addHidden(const int shownIndex)
{
    if(!shownIndexBoundsCheck(shownIndex))
        return -1;

    hiddenData.append(getInstanceValues(shownIndex));

    removeShown(shownIndex);

    return hidden++;
}

bool IEInstRenderable::removeHidden(const int index)
{
    if(!hiddenIndexBoundsCheck(index))
        return false;

    const int lastIndex = hiddenData.size() - 1;

    hiddenData[index] = hiddenData[lastIndex];
    hiddenData.removeLast();
    hidden--;

    return true;
}

QHash<QString, std::any> IEInstRenderable::getInstanceValues(const int shownIndex)
{
    if(!shownIndexBoundsCheck(shownIndex))
        return QHash<QString, std::any>{};

    QHash<QString, std::any> results;
    QHashIterator<QString, IEBufferObject*> it(buffers);
    while(it.hasNext())
    {
        it.next();

        auto* buffer = it.value();
        if(!buffer->getIsInstanced())
            continue;

        results.insert(it.key(), buffer->getValue(shownIndex));
    }

    return results;
}

bool IEInstRenderable::shownIndexBoundsCheck(const int index)
{
    return (index > -1 && index < shown);
}

bool IEInstRenderable::hiddenIndexBoundsCheck(const int index)
{
    return (index > -1 && index < hidden);
}

QDataStream& IEInstRenderable::serialize(QDataStream& out, const Serializable& obj) const
{
    IERenderable::serialize(out, obj);

    const auto& renderable = static_cast<const IEInstRenderable&>(obj);

    out << renderable.hiddenData.size();
    for(int i = 0; i < renderable.hiddenData.size(); i++)
    {
        out << renderable.hiddenData[i].size();

        QHashIterator<QString, std::any> it(renderable.hiddenData[i]);
        while(it.hasNext())
        {
            it.next();

            const std::any& info = it.value();
            size_t hashcode = info.type().hash_code();

            out << it.key() << hashcode;

            if(hashcode == typeid(QVector2D).hash_code())
                out << std::any_cast<QVector2D>(info);
            else if(hashcode == typeid(QVector3D).hash_code())
                out << std::any_cast<QVector3D>(info);
            else if(hashcode == typeid(QVector4D).hash_code())
                out << std::any_cast<QVector4D>(info);
            else if(hashcode == typeid(QMatrix4x4).hash_code())
                out << std::any_cast<QMatrix4x4>(info);
            else
                out << -1;
        }
    }

    out << renderable.shown << renderable.hidden;

    return out;
}

QDataStream& IEInstRenderable::deserialize(QDataStream& in, Serializable& obj)
{
    IERenderable::deserialize(in, obj);

    auto& renderable = static_cast<IEInstRenderable&>(obj);
    renderable.hiddenData.clear();

    int hiddenInstanceSize = 0;
    in >> hiddenInstanceSize;

    for(int i = 0; i < hiddenInstanceSize; i++)
    {
        int dataSize = 0;
        in >> dataSize;

        QHash<QString, std::any> results;

        for(int j = 0; j < dataSize; j++)
        {
            QString bufferName = "";
            size_t hashcode = 0;
            std::any data;
            in >> bufferName >> hashcode;

            if(hashcode == typeid(QVector2D).hash_code())
            {
                QVector2D temp;
                in >> temp;
                data = temp;
            }
            else if(hashcode == typeid(QVector3D).hash_code())
            {
                QVector3D temp;
                in >> temp;
                data = temp;
            }
            else if(hashcode == typeid(QVector4D).hash_code())
            {
                QVector4D temp;
                in >> temp;
                data = temp;
            }
            else if(hashcode == typeid(QMatrix4x4).hash_code())
            {
                QMatrix4x4 temp;
                in >> temp;
                data = temp;
            }

            results.insert(bufferName, data);
        }

        renderable.hiddenData.append(results);
    }

    in >> renderable.shown >> renderable.hidden;

    return in;
}
