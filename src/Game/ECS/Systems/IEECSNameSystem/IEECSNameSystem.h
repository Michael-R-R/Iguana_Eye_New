#pragma once

#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;

class IEECSNameSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> nameKey;
        QVector<unsigned long long> tagKey;
        QVector<int> tagIndex;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.nameKey
                << data.tagKey << data.tagIndex;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.nameKey
               >> data.tagKey >> data.tagIndex;
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

    void startup(const GameStartEvent& event) override;
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
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

