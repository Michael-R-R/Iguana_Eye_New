#pragma once

#include <QDataStream>
#include <map>

#include "IEObject.h"

template <class T>
class IEResourceContainer : public IEObject
{
    std::map<unsigned long long, std::unique_ptr<T>> resources;

public:
    IEResourceContainer() :
        IEObject(), resources()
    {
        IEResourceContainer::add(0, std::move(std::make_unique<T>()));
    }

    ~IEResourceContainer()
    {
        clear();
    }

    bool add(const unsigned long long key, std::unique_ptr<T> resource)
    {
        if(!resource)
            return false;

        if(doesExist(key))
            return false;

        resources[key] = std::move(resource);

        return true;
    }

    bool remove(const unsigned long long key)
    {
        if(!doesExist(key))
            return false;

        resources.erase(key);

        return true;
    }

    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey)
    {
        if(!doesExist(oldKey) || doesExist(newKey))
            return false;

        auto temp = std::move(resources[oldKey]);
        resources.erase(oldKey);
        resources[newKey] = std::move(temp);

        return true;
    }

    void clear()
    {
        resources.clear();
    }

    T& getValue(const unsigned long long key) const
    {
        if(!doesExist(key))
            return *resources.at(0);

        return *resources.at(key);
    }

    bool doesExist(const unsigned long long key) const
    {
        return (resources.find(key) != resources.end());
    }

    const std::map<unsigned long long, std::unique_ptr<T>>* getResources() const { return &resources; }
};
