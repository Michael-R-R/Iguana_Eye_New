#pragma once

#include <QMap>
#include <QSharedPointer>

#include "IEObject.h"

template <class T>
class IEResourceManager : public IEObject
{
protected:
    QMap<unsigned long long, QSharedPointer<T>> resources;

public:
    IEResourceManager() : resources()
    {

    }

    ~IEResourceManager()
    {

    }

    virtual bool add(const unsigned long long key, QSharedPointer<T> value)
    {
        if(!value || doesExist(key))
            return false;

        resources[key] = value;

        return true;
    }

    virtual bool remove(const unsigned long long key)
    {
        if(!doesExist(key))
            return false;

        resources.remove(key);

        return true;
    }

    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey)
    {
        if(!doesExist(oldKey) || doesExist(newKey))
            return false;

        auto temp = resources[oldKey];
        resources.remove(oldKey);
        resources[newKey] = temp;

        return true;
    }

    QSharedPointer<T> value(const unsigned long long key) const
    {
        if(!doesExist(key))
            return nullptr;

        return resources[key];
    }

    bool doesExist(const unsigned long long key) const
    {
        return resources.contains(key);
    }

    void clear()
    {
        resources.clear();
    }

    const QMap<unsigned long long, QSharedPointer<T>>& getResources() const
    {
        return resources;
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override
    {
        const auto& manager = static_cast<const IEResourceManager&>(obj);

        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            out << *i;
        }

        return out;
    }

    QDataStream& deserialize(QDataStream& in, Serializable& obj) override
    {
        auto& manager = static_cast<IEResourceManager&>(obj);
        manager.clear();

        int size = 0;
        in >> size;

        for(int i = 0; i < size; i++)
        {
            auto resource = QSharedPointer<T>::create();

            in >> *resource;

            manager.add(resource->getId(), resource);
        }

        return in;
    }
};
