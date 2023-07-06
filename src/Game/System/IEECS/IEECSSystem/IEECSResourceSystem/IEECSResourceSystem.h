#pragma once

#include <QVector>
#include <QHash>
#include <QSet>

#include "IEECSSystem.h"
#include "IEEntity.h"
#include "IEResourceManager.h"

class IEECSResourceSystem : public IEECSSystem
{
protected:
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<uint64_t> resourceId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.resourceId;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.resourceId;
            return in;
        }
    };

    Data data;
    QHash<uint64_t, QSet<int>> idIndexPair;

public:
    IEECSResourceSystem(size_t id, QObject* parent = nullptr);
    virtual ~IEECSResourceSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;

    virtual QSet<int> massReplaceResourceId(const uint64_t oldId, const uint64_t newId);
    virtual QSet<int> massPurgeResourceId(uint64_t id);

    bool doesResourceIdExist(const uint64_t id);

    uint64_t getResourceId(const int index);
    void setResourceId(const int index, uint64_t val);

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

protected:
    template<class T>
    T* getAttachedResource(const int index, IEResourceManager* manager)
    {
        if(!indexBoundCheck(index))
            return nullptr;

        return static_cast<T*>(manager->value<T>(data.resourceId[index]));
    }
};

