#pragma once

#include <QDataStream>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

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

public:
    IEECSTransformSystem();
    ~IEECSTransformSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

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

