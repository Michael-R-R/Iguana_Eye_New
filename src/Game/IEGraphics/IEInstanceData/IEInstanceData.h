#pragma once

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
    ~IEInstanceData() {}

    int add(const IEEntity entity);
    std::tuple<IEEntity, int> remove(const IEEntity& entity);
    int count() const;
    bool doesExist(const IEEntity& entity) const;
};

