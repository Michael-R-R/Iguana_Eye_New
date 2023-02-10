#pragma once

#include <QDataStream>
#include <QMap>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;
class IEECSHierarchySystem;

class IEECSTransformSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<QVector3D> positionList;
        QVector<QVector3D> rotationList;
        QVector<QVector3D> scaleList;
        QVector<QMatrix4x4> transformList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.positionList << data.rotationList
                << data.scaleList << data.transformList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.positionList >> data.rotationList
               >> data.scaleList >> data.transformList;
            return in;
        }
    };

    Data data;

    QMap<IEEntity, int> dirtyParents;

public:
    IEECSTransformSystem();
    ~IEECSTransformSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

    const QVector3D& getPosition(const int index) const;
    const QVector3D& getRotation(const int index) const;
    const QVector3D& getScale(const int index) const;
    const QMatrix4x4& getTransform(const int index) const;

    void setPosition(const int index, const QVector3D& val);
    void setRotation(const int index, const QVector3D& val);
    void setScale(const int index, const QVector3D& val);
    void setTransform(const int index, const QMatrix4x4& val);

private:
    void updateTransform(const int index,
                         QMap<IEEntity, int>& dirtyChildren,
                         const IEECSHierarchySystem* hierarchySystem);
    QMatrix4x4 calcModelMatrix(const int index);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEECSTransformSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSTransformSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

