#pragma once

#include <QSharedPointer>
#include <QString>
#include <QMap>

#include "IEVertexBuffer.h"
#include "Serializable.h"

template <class T>
class IEVertexBufferContainer : public Serializable
{
    QMap<QString, QSharedPointer<IEVertexBuffer<T>>> buffers;

public:
    IEVertexBufferContainer() : buffers() {}
    IEVertexBufferContainer(const IEVertexBufferContainer& other) = delete;
    ~IEVertexBufferContainer() {}

    bool add(const QString key, QSharedPointer<IEVertexBuffer<T>> value)
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

        buffers.remove(key);

        return true;
    }

    void clear()
    {
        buffers.clear();
    }

    void releaseAllBuffers()
    {
        for(auto& i : buffers)
        {
            i->release();
        }
    }

    bool doesExist(const QString& key) const
    {
        return buffers.contains(key);
    }

    QSharedPointer<IEVertexBuffer<T>> value(const QString& key) const
    {
        if(!doesExist(key))
            return nullptr;

        return buffers[key];
    }

    const QMap<QString, QSharedPointer<IEVertexBuffer<T>>>& getBuffers() const { return buffers; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override
    {
        const auto& container = static_cast<const IEVertexBufferContainer&>(obj);

        out << (int)container.buffers.size();

        QMapIterator<QString, QSharedPointer<IEVertexBuffer<T>>> it(container.buffers);
        while(it.hasNext())
        {
            it.next();
            out << it.key() << *it.value();
        }

        return out;
    }

    QDataStream& deserialize(QDataStream &in, Serializable &obj) override
    {
        auto& container = static_cast<IEVertexBufferContainer&>(obj);
        container.clear();

        int size = 0;
        in >> size;

        QString key;

        for(int i = 0; i < size; i++)
        {
            in >> key;

            auto value = QSharedPointer<IEVertexBuffer<T>>::create();

            in >> *value;

            container.buffers[key] = value;
        }

        return in;
    }
};
