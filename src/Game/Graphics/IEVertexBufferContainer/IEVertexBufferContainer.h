#pragma once

#include <QString>
#include <QMap>

#include "IEObject.h"
#include "IEVertexBuffer.h"

template <class T>
class IEVertexBufferContainer : public IEObject
{
    QMap<QString, IEVertexBuffer<T>*> buffers;

public:
    IEVertexBufferContainer(QObject* parent = nullptr) : IEObject(parent), buffers() {}
    IEVertexBufferContainer(const IEVertexBufferContainer& other) = delete;
    ~IEVertexBufferContainer() {}

    bool add(const QString key, IEVertexBuffer<T>* value)
    {
        if(doesExist(key))
            return false;

        buffers[key] = value;
        value->setParent(this);

        return true;
    }

    bool remove(const QString& key)
    {
        if(!doesExist(key))
            return false;

        auto* temp = buffers[key];
        buffers.remove(key);
        delete temp;

        return true;
    }

    void clear()
    {
        for(auto* i : buffers)
        {
            delete i;
        }

        buffers.clear();
    }

    void releaseAllBuffers()
    {
        for(auto* i : buffers)
        {
            i->release();
        }
    }

    bool doesExist(const QString& key) const
    {
        return buffers.contains(key);
    }

    IEVertexBuffer<T>* value(const QString& key) const
    {
        if(!doesExist(key))
            return nullptr;

        return buffers[key];
    }

    const QMap<QString, IEVertexBuffer<T>*>& getBuffers() const { return buffers; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override
    {
        const auto& container = static_cast<const IEVertexBufferContainer&>(obj);

        out << (int)container.buffers.size();

        QMapIterator<QString, IEVertexBuffer<T>*> it(container.buffers);
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

            auto value = new IEVertexBuffer<T>(&container);

            in >> *value;

            if(!container.add(key, value))
                delete value;
        }

        return in;
    }
};
