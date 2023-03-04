#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IECameraManager;
class IECamera;

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

    int activeIndex;

    // DOES NOT OWN THIS POINTER
    IECameraManager* cameraManager;

public:
    IEECSCameraSystem();
    ~IEECSCameraSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    IECamera* getActiveCamera() const;
    IECamera* getAttachedCamera(const int index) const;
    void setActiveIndex(const int val);

    unsigned long long getCameraId(const int index) const;
    void setCameraId(const int index, const unsigned long long val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSCameraSystem& system)
    {
        out << system.entityMap << system.data << system.activeIndex;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSCameraSystem& system)
    {
        in >> system.entityMap >> system.data >> system.activeIndex;
        return in;
    }
};

