#pragma once

#include <QDataStream>
#include <QMap>

#include "IEObject.h"

template <class T>
class IEResourceContainer : public IEObject
{
    QMap<unsigned long long, T*> resources;

public:
    IEResourceContainer() :
        IEObject(), resources()
    {

    }

    ~IEResourceContainer()
    {
        clear();
    }

    bool add(const unsigned long long key, T* resource)
    {
        if(!resource)
            return false;

        if(doesExist(key))
        {
            delete resource;
            return false;
        }

        resources[key] = resource;

        return true;
    }

    bool remove(const unsigned long long key)
    {
        if(!doesExist(key))
            return false;

        T* temp = resources[key];
        resources.remove(key);
        delete temp;

        return true;
    }

    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey)
    {
        if(!doesExist(oldKey) || doesExist(newKey))
            return false;

        T* temp = resources[oldKey];
        resources.remove(oldKey);
        resources[newKey] = temp;

        return true;
    }

    void clear()
    {
        QMapIterator<unsigned long long, T*> it(resources);
        while(it.hasNext())
        {
            it.next();

            T* temp = it.value();
            delete temp;
            temp = nullptr;
        }

        resources.clear();
    }

    unsigned long long getKey(const T* value) const
    {
        if(!doesExist(value))
            return false;
        return resources.key(value);
    }

    T* getValue(const unsigned long long key) const
    {
        if(!doesExist(key))
            return nullptr;
        return resources[key];
    }

    bool doesExist(const unsigned long long key) const
    {
        return resources.contains(key);
    }

    bool doesExist(const T* value) const
    {
        return (std::find(resources.begin(), resources.end(), value) != resources.end());
    }

    const QMap<unsigned long long, T*>& getResources() const { return resources; }
};
