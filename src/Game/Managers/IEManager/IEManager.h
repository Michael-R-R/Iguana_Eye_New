#pragma once

#include "IEObject.h"
#include "IEResourceContainer.h"

template <class T>
class IEManager : public IEObject
{
protected:
    IEResourceContainer<T>* resourceContainer;

public:
    IEManager(QObject* parent = nullptr) :
        IEObject(parent),
        resourceContainer(new IEResourceContainer<QString>(this))
    {

    }

    ~IEManager()
    {

    }

    virtual bool add(const unsigned long long key, T* value)
    {
        if(!resourceContainer->add(key, value))
            return false;

        return true;
    }

    virtual bool remove(const unsigned long long key)
    {
        if(!resourceContainer->remove(key))
            return false;

        return true;
    }

    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey)
    {
        if(!resourceContainer->changeKey(oldKey, newKey))
            return false;

        return true;
    }

    bool doesExist(const unsigned long long key) const
    {
        return resourceContainer->doesExist(key);
    }

    bool doesExist(const T* value) const
    {
        return resourceContainer->doesExist(value);
    }

    const T* getValue(const unsigned long long key) const
    {
        return resourceContainer->getValue(key);
    }

    IEResourceContainer<T>* getResourceContainer() const
    {
        return resourceContainer;
    }

    void setResourceContainer(IEResourceContainer<T>* val)
    {
        resourceContainer = val;
    }
};
