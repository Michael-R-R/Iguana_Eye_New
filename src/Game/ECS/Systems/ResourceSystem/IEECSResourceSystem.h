#pragma once

#include <QVector>
#include <QMap>
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
        QVector<unsigned long long> resourceId;

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
    QMap<unsigned long long, QSet<int>> idIndexPair;

public:
    IEECSResourceSystem(QObject* parent = nullptr);
    ~IEECSResourceSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;

    virtual QSet<int> massReplaceResourceId(const unsigned long long oldId, const unsigned long long newId);
    virtual QSet<int> massPurgeResourceId(unsigned long long id);

    bool doesResourceIdExist(const unsigned long long id);

    unsigned long long getResourceId(const int index);
    void setResourceId(const int index, unsigned long long val);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

protected:
    template<class T>
    T* getAttachedResource(const int index, IEResourceManager* manager)
    {
        if(!indexBoundCheck(index))
            return nullptr;

        return static_cast<T*>(manager->value<T>(data.resourceId[index]));
    }
};

