#pragma once

#include "IEObject.h"
#include "IEResourceContainer.h"

class GameStartEvent;

template <class T>
class IEManager : public IEObject
{
protected:
    IEResourceContainer<T>* resourceContainer;

public:
    IEManager(QObject* parent = nullptr) :
        IEObject(parent),
        resourceContainer(new IEResourceContainer<T>(this))
    {

    }

    ~IEManager()
    {

    }

    virtual void startup(const GameStartEvent& event) = 0;
    virtual void shutdown() = 0;

    virtual bool add(const unsigned long long key, T* value)
    {
        return resourceContainer->add(key, value);
    }

    virtual bool remove(const unsigned long long key)
    {
        return resourceContainer->remove(key);
    }

    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey)
    {
        return resourceContainer->changeKey(oldKey, newKey);
    }

    bool doesExist(const unsigned long long key) const
    {
        return resourceContainer->doesExist(key);
    }

    bool doesExist(const T* value) const
    {
        return resourceContainer->doesExist(value);
    }

    T* getValue(const unsigned long long key) const
    {
        return resourceContainer->getValue(key);
    }

    IEResourceContainer<T>* getResourceContainer() const
    {
        return resourceContainer;
    }
};
