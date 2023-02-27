#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <tuple>

#include "IEEntity.h"

class IEInstanceData
{
    QMap<IEEntity, int> entityMap;
    QVector<IEEntity> entityList;

public:
    IEInstanceData();
    IEInstanceData(const IEInstanceData& other);
    ~IEInstanceData() {}

    int add(const IEEntity& entity);
    std::tuple<IEEntity, int> remove(const IEEntity& entity);
    int count() const;
    bool doesExist(const IEEntity& entity) const;
    int lookUpIndex(const IEEntity& entity) const;

    friend QDataStream& operator<<(QDataStream& out, const IEInstanceData& data)
    {
        out << data.entityMap << data.entityList;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEInstanceData& data)
    {
        in >> data.entityMap >> data.entityList;

        return in;
    }
};

