#pragma once

#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class IEECSNameSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<uint64_t> nameKey;
        QVector<uint64_t> tagKey;
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

    QMap<uint64_t, QString> nameMap;
    QMap<uint64_t, QString> tagNameMap;
    QMap<uint64_t, QVector<IEEntity>> tagEntityMap;

public:
    IEECSNameSystem(QObject* parent = nullptr);
    ~IEECSNameSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;

    void addNameTag(const QString& name);
    void clearNameTag(const QString& name);
    void clearEntityTag(const int index);
    QVector<IEEntity> getEntityTagList(const QString& tagName) const;

    uint64_t getNameKey(const int index) const;
    uint64_t getTagKey(const int index) const;
    int getTagIndex(const int index) const;
    QString getName(const int index) const;
    QString getTagName(const int index) const;

    void setName(const int index, const QString& val);
    void setTag(const int index, const QString& val);

private:
    std::tuple<uint64_t, QString> hashString(const QString& value);
    void removeName(const uint64_t key);
    void removeNameTag(const uint64_t key);
    void removeEntityTag(const uint64_t key, const int indexToRemove);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

