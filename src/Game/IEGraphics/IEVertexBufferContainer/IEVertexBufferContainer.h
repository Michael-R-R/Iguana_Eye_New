#pragma once

#include <QDataStream>
#include <QMap>
#include <QString>
#include <QVector>

#include "IEVertexBuffer.h"

template <class T>
class IEVertexBufferContainer
{
    QMap<QString, IEVertexBuffer<T>*> buffers;

public:
    IEVertexBufferContainer() :
        buffers()
    {

    }

    IEVertexBufferContainer(const IEVertexBufferContainer& other) :
        buffers()
    {
        QMap<QString, IEVertexBuffer<T>*> tempBuffers;
        QMapIterator<QString, IEVertexBuffer<T>*> it(other.buffers);
        while(it.hasNext())
        {
            it.next();
            tempBuffers[it.key()] = new IEVertexBuffer<T>();
        }

        buffers = tempBuffers;
    }

    ~IEVertexBufferContainer()
    {
        clear();
    }

    bool add(const QString key, IEVertexBuffer<T>* value)
    {
        if(doesExist(key))
        {
            delete value;
            return false;
        }

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
        QMapIterator<QString, IEVertexBuffer<T>*> it(buffers);
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

    IEVertexBuffer<T>* getValue(const QString& key) const
    {
        if(!doesExist(key))
            return nullptr;

        return buffers[key];
    }

    const QMap<QString, IEVertexBuffer<T>*>& getBuffers() const { return buffers; }

    friend QDataStream& operator<<(QDataStream& out, const IEVertexBufferContainer<T>& container)
    {
        out << (int)container.buffers.size();

        QMapIterator<QString, IEVertexBuffer<T>*> it(container.buffers);
        while(it.hasNext())
        {
            it.next();
            out << it.key()
                << *it.value();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEVertexBufferContainer<T>& container)
    {
        int size = 0;
        in >> size;

        QString key;
        IEVertexBuffer<T>* value = nullptr;

        container.clear();
        for(int i = 0; i < size; i++)
        {
            in >> key;

            value = new IEVertexBuffer<T>();

            in >> *value;

            container.buffers[key] = value;
        }

        return in;
    }
};
