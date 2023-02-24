#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class IEECSNameSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> nameKeyList;
        QVector<unsigned long long> tagKeyList;
        QVector<int> tagIndexList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.nameKeyList
                << data.tagKeyList << data.tagIndexList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.nameKeyList
               >> data.tagKeyList >> data.tagIndexList;
            return in;
        }
    };

    Data data;

    QMap<unsigned long long, QString> nameMap;
    QMap<unsigned long long, QString> tagNameMap;
    QMap<unsigned long long, QVector<IEEntity>> tagEntityMap;

public:
    IEECSNameSystem();
    ~IEECSNameSystem() {}

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void addNameTag(const QString& name);
    void clearNameTag(const QString& name);
    void clearEntityTag(const int index);
    QVector<IEEntity> getEntityTagList(const QString& name) const;

    unsigned long long getNameKey(const int index) const;
    unsigned long long getTagKey(const int index) const;
    int getTagIndex(const int index) const;
    QString getName(const int index) const;
    QString getTagName(const int index) const;

    void setName(const int index, const QString& val);
    void setTag(const int index, const QString& val);

private:
    std::tuple<unsigned long long, QString> hashString(const QString& value);
    void removeName(const unsigned long long key);
    void removeNameTag(const unsigned long long key);
    void removeEntityTag(const unsigned long long key, const int indexToRemove);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEECSNameSystem& system)
    {
        out << system.entityMap << system.data << system.nameMap
            << system.tagNameMap << system.tagEntityMap;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSNameSystem& system)
    {
        in >> system.entityMap >> system.data >> system.nameMap
           >> system.tagNameMap >> system.tagEntityMap;
        return in;
    }
};

