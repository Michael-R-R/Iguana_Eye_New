#pragma once

#include <QMap>
#include <QSharedPointer>

#include "IEObject.h"

template <class T>
class IEResourceManager : public IEObject
{
protected:
    unsigned long long defaultResourceId;
    QMap<unsigned long long, QSharedPointer<T>> resources;

public:
    IEResourceManager() :
        resources(),
        defaultResourceId(0)
    {

    }

    ~IEResourceManager()
    {

    }

    virtual bool add(const unsigned long long key, QSharedPointer<T> value) = 0;
    virtual bool remove(const unsigned long long key) = 0;
    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) = 0;

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

    unsigned long long getDefaultResourceId() const
    {
        return defaultResourceId;
    }

    void setDefaultResourceId(const unsigned long long val)
    {
        defaultResourceId = val;
    }
};
