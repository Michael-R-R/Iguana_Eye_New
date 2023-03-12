#pragma once

#include <map>
#include <memory>

#include "IEObject.h"

class GameStartEvent;

template <class T>
class IEResourceManager : public IEObject
{
protected:
    unsigned long long defaultResourceId;
    std::map<unsigned long long, std::unique_ptr<T>> resources;

public:
    IEResourceManager() :
        resources(),
        defaultResourceId(0)
    {

    }

    ~IEResourceManager()
    {

    }

    virtual void startup(const GameStartEvent& event) = 0;
    virtual void shutdown() = 0;
    virtual bool add(const unsigned long long key, std::unique_ptr<T> value) = 0;
    virtual bool remove(const unsigned long long key) = 0;
    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) = 0;

    T* value(const unsigned long long key) const
    {
        if(!doesExist(key))
            return nullptr;

        return &(*resources.at(key));
    }

    bool doesExist(const unsigned long long key) const
    {
        return (resources.find(key) != resources.end());
    }

    void clear()
    {
        resources.clear();
    }

    const std::map<unsigned long long, std::unique_ptr<T>>* getResources() const
    {
        return &resources;
    }

    unsigned long long getDefaultResourceId() const
    {
        return defaultResourceId;
    }

    void setDefaultResourceId(const unsigned long long val)
    {
        defaultResourceId = val;
    }
};
