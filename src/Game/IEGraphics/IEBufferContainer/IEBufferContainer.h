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
        QMap<QString, IEBuffer<T>*> tempBuffers;

        QMapIterator<QString, IEBuffer<T>*> it(other.buffers);
        while(it.hasNext())
        {
            it.next();
            tempBuffers[it.key()] = new IEBuffer<T>(*it.value());;
        }

        buffers = tempBuffers;
    }

    ~IEBufferContainer()
    {
        clear();
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

    void releaseAllBuffers()
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

    IEBuffer<T>* getValue(const QString& key) const
    {
        if(!doesExist(key))
            return nullptr;

        return buffers[key];
    }

    const QMap<QString, IEBuffer<T>*>& getBuffers() const { return buffers; }

    friend QDataStream& operator<<(QDataStream& out, const IEBufferContainer<T>& container)
    {
        out << (int)container.buffers.size();

        QMapIterator<QString, IEBuffer<T>*> it(container.buffers);
        while(it.hasNext())
        {
            it.next();
            out << it.key()
                << it.value()->type()
                << *it.value();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEBufferContainer<T>& container)
    {
        int size = 0;
        in >> size;

        QString key;
        QOpenGLBuffer::Type type;

        for(int i = 0; i < size; i++)
        {
            in >> key >> type;

            auto buffer = new IEBuffer<T>(type);

            in >> *buffer;

            container.buffers[key] = buffer;
        }

        return in;
    }
};
