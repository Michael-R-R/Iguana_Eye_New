#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;

class IEECSCameraSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> cameraId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.cameraId;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.cameraId;
            return in;
        }
    };

    Data data;

public:
    IEECSCameraSystem();
    ~IEECSCameraSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    friend QDataStream& operator<<(QDataStream& out, const IEECSCameraSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSCameraSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

