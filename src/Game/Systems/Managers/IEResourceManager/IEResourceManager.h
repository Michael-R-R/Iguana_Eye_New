#pragma once

#include <QHash>

#include "IEGameSystem.h"

class IEResource;

class IEResourceManager : public IEGameSystem
{
    Q_OBJECT

protected:
    QHash<uint64_t, IEResource*> resources;
    uint64_t defaultId;

public:
    IEResourceManager(QObject* parent = nullptr);
    IEResourceManager(const IEResourceManager&) = delete;
    virtual ~IEResourceManager();

    void shutdown(IEGame&) override;
    void onDeserialize(IEGame&) override;

    virtual bool add(const uint64_t key, IEResource* value);
    virtual bool remove(const uint64_t key);
    virtual bool changeKey(const uint64_t oldKey, const uint64_t newKey);

    bool doesExist(const uint64_t key) const;
    void clear();

    uint64_t getDefaultId() const { return defaultId; }
    QHash<uint64_t, IEResource*>& getResources() { return resources; }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

signals:
    void added(const uint64_t key, const QString& path);
    void removed(const uint64_t key);
    void keyChanged(const uint64_t oldKey, const uint64_t newKey);

public:
    template<class T>
    T* value(const uint64_t key)
    {
        if(!doesExist(key))
            return nullptr;

        return static_cast<T*>(resources[key]);
    }
};
