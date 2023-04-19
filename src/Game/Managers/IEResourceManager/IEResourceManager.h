#pragma once

#include <QMap>

#include "IEObject.h"

class IEResource;

class IEResourceManager : public IEObject
{
    Q_OBJECT

protected:
    QMap<unsigned long long, IEResource*> resources;
    unsigned long long defaultId;

public:
    IEResourceManager(QObject* parent = nullptr);
    virtual ~IEResourceManager();

    virtual void startup() {}
    virtual void shutdown() {}

    virtual bool add(const unsigned long long key, IEResource* value);
    virtual bool remove(const unsigned long long key);
    virtual bool changeKey(const unsigned long long oldKey, const unsigned long long newKey);

    bool doesExist(const unsigned long long key) const;
    void clear();

    unsigned long long getDefaultId() const { return defaultId; }
    QMap<unsigned long long, IEResource*>& getResources() { return resources; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

    template<class T>
    T* value(const unsigned long long key)
    {
        if(!doesExist(key))
            return nullptr;

        return static_cast<T*>(resources[key]);
    }

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);
};
