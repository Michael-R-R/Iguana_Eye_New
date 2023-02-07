#pragma once

#include <QDataStream>
#include <QMap>
#include <QString>
#include <QVector>

#include "IEBuffer.h"

template <class T>
class IEBufferContainer
{
    QMap<QString, IEBuffer<T>*> buffers;

public:
    IEBufferContainer() :
        buffers()
    {

    }

    IEBufferContainer(const IEBufferContainer& other) :
        buffers()
    {
        QMap<QString, IEBuffer*> tempBuffers;

        QMapIterator<QString, IEBuffer*> it(other.buffers);
        while(it.hasNext())
        {
            tempBuffers[it.key()] = new IEBuffer(*it.value());;
        }

        buffers = tempBuffers;
    }

    ~IEBufferContainer()
    {
        clear();
    }

    void clear()
    {
        QMapIterator<QString, IEBuffer<T>*> it(buffers);
        while(it.hasNext())
        {
            it.next();

            auto temp = it.value();
            buffers[it.key()] = nullptr;
            delete temp;
        }

        buffers.clear();
    }

    bool add(const QString key, IEBuffer<T>* value)
    {
        if(doesExist(key))
            return false;

        buffers[key] = value;

        return true;
    }

    bool remove(const QString& key)
    {
        if(!doesExist(key))
            return false;

        auto temp = buffers[key];
        buffers.remove(key);
        delete temp;

        return true;
    }

    bool bind(const QString& key)
    {
        if(!doesExist(key))
            return false;

        buffers[key]->bind();

        return true;
    }

    bool release(const QString& key)
    {
        if(!doesExist(key))
            return false;

        buffers[key]->release();

        return true;
    }

    void releaseAll()
    {
        for(auto& buffer : buffers)
        {
            buffer->release();
        }
    }

    bool doesExist(const QString& key) const
    {
        return buffers.contains(key);
    }

    void rebuildBuffer(const QString& key, const int attribLoc)
    {
        if(!doesExist(key))
            return;

        buffers[key]->rebuild(attribLoc);
    }

    void subAllocateBuffer(const QString& key, int offset, T& data)
    {
        if(!doesExist(key))
            return;

        buffers[key]->subAllocate(offset, data);
    }

    const QMap<QString, IEBuffer<T>*>& getBuffers() const { return buffers; }
    void setBuffers(const QMap<QString, IEBuffer<T>*> val) { buffers = val; }
};

template <class T>
QDataStream& operator<<(QDataStream& out, const IEBufferContainer<T>& container)
{
    int size = container.getBuffers().size();
    out << size;

    QMapIterator<QString, IEBuffer<T>*> it(container.getBuffers());
    while(it.hasNext())
    {
        it.next();

        out << it.key() << it.value()->type() << *it.value();
    }

    return out;
}

template <class T>
QDataStream& operator>>(QDataStream& in, IEBufferContainer<T>& container)
{
    int size = 0;
    in >> size;

    QMap<QString, IEBuffer<T>*> tempBuffers;
    for(int i = 0; i < size; i++)
    {
        QString key;
        QOpenGLBuffer::Type type;
        in >> key >> type;

        auto buffer = new IEBuffer<T>(type);
        in >> *buffer;

        tempBuffers[key] = buffer;
    }

    container.setBuffers(tempBuffers);

    return in;
}
