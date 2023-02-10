#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSHierarchySystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<IEEntity> parentList;
        QVector<QVector<IEEntity>> childrenList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.parentList << data.childrenList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.parentList >> data.childrenList;
            return in;
        }
    };

    Data data;

public:
    IEECSHierarchySystem();
    ~IEECSHierarchySystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

    void addChild(const int parentIndex, const IEEntity childEntity);
    void removeChild(const int parentIndex, IEEntity childEntity);
    void moveChild(const int oldParentIndex, const int newParentIndex, const IEEntity childEntity);

    IEEntity getEntity(const int index) const;
    IEEntity getParent(const int index) const;
    const QVector<IEEntity>& getChildrenList(const int index) const;

    friend QDataStream& operator<<(QDataStream& out, const IEECSHierarchySystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSHierarchySystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};
