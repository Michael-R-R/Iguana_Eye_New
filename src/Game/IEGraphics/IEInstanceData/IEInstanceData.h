#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QString>
#include <tuple>

#include "IEEntity.h"

class IEInstanceData
{
    QMap<IEEntity, int> shownEntityMap;
    QVector<IEEntity> shownEntityList;

    QMap<IEEntity, int> hiddenEntityMap;
    QVector<IEEntity> hiddenEntityList;

public:
    IEInstanceData();
    IEInstanceData(const IEInstanceData& other);
    ~IEInstanceData() {}

    int addShown(const IEEntity& entity);
    std::tuple<IEEntity, int> removeShown(const IEEntity& entity);
    int shownCount() const;
    bool doesExistShown(const IEEntity& entity) const;
    int lookUpShownIndex(const IEEntity& entity) const;

    int addHidden(const IEEntity& entity);
    std::tuple<IEEntity, int> removeHidden(const IEEntity& entity);
    int hiddenCount() const;
    bool doesExistHidden(const IEEntity& entity) const;
    int lookUpHiddenIndex(const IEEntity& entity) const;

private:
    int add(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);
    std::tuple<IEEntity, int> remove(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEInstanceData& data)
    {
        out << data.shownEntityMap << data.shownEntityList
            << data.hiddenEntityMap << data.hiddenEntityList;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEInstanceData& data)
    {
        in >> data.shownEntityMap >> data.shownEntityList
           >> data.hiddenEntityMap >> data.hiddenEntityList;

        return in;
    }
};

