#pragma once

#include <QString>
#include <map>
#include <memory>

#include "IEVertexBuffer.h"
#include "Serializable.h"

template <class T>
class IEVertexBufferContainer : public Serializable
{
    std::map<QString, std::unique_ptr<IEVertexBuffer<T>>> buffers;

public:
    IEVertexBufferContainer() :
        buffers()
    {

    }

    IEVertexBufferContainer(const IEVertexBufferContainer& other) :
        buffers()
    {
        for(auto& i : other.buffers)
        {
            auto tempBuffer = std::make_unique<IEVertexBuffer<T>>(*i.second);
            buffers[i.first] = std::move(tempBuffer);
        }
    }

    ~IEVertexBufferContainer()
    {

    }

    bool add(const QString key, std::unique_ptr<IEVertexBuffer<T>> value)
    {
        if(doesExist(key))
            return false;

        buffers[key] = std::move(value);

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
            i.second->release();
        }
    }

    bool doesExist(const QString& key) const
    {
        return (buffers.find(key) != buffers.end());
    }

    IEVertexBuffer<T>* value(const QString& key) const
    {
        if(!doesExist(key))
            return nullptr;

        return &(*buffers.at(key));
    }

    const std::map<QString, std::unique_ptr<IEVertexBuffer<T>>>* getBuffers() const { return &buffers; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override
    {
        const auto& container = static_cast<const IEVertexBufferContainer&>(obj);

        out << (int)container.buffers.size();

        for(auto& i : container.buffers)
        {
            out << i.first << *i.second;
        }

        return out;
    }

    QDataStream& deserialize(QDataStream &in, Serializable &obj) override
    {
        auto& container = static_cast<IEVertexBufferContainer&>(obj);

        int size = 0;
        in >> size;

        QString key;

        container.clear();
        for(int i = 0; i < size; i++)
        {
            in >> key;

            auto value = std::make_unique<IEVertexBuffer<T>>();

            in >> *value;

            container.buffers[key] = std::move(value);
        }

        return in;
    }
};
