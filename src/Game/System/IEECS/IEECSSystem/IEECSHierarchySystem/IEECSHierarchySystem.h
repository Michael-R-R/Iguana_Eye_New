#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class IEECSHierarchySystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<IEEntity> parent;
        QVector<QVector<IEEntity>> children;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.parent << data.children;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.parent >> data.children;
            return in;
        }
    };

    Data data;

public:
    IEECSHierarchySystem(QObject* parent = nullptr);
    ~IEECSHierarchySystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;

    void addChild(const int parentIndex, const IEEntity childEntity);
    void removeChild(const int parentIndex, IEEntity childEntity);
    void moveChild(const int oldParentIndex, const int newParentIndex, const IEEntity childEntity);

    IEEntity getEntity(const int index) const;
    IEEntity getParent(const int index) const;
    const QVector<IEEntity>& getChildrenList(const int index) const;

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
