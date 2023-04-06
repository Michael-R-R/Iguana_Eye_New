#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"
#include "IECameraScript.h"

class IEGame;
class IECameraManager;
class IECamera;
class ECSOnUpdateEvent;

class IEECSCameraSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<IECameraScript> cameraScript;
        QVector<unsigned long long> cameraId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.cameraId << data.cameraScript;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.cameraId >> data.cameraScript;
            return in;
        }
    };

    Data data;

    int activeIndex;

    IECameraManager& cameraManager;

public:
    IEECSCameraSystem(IEGame& game);
    ~IEECSCameraSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void play(IEGame& game) override;

    int getActiveIndex() const;
    IEEntity getActiveEntity() const;
    IECamera* getActiveCamera() const;
    IECamera* getAttachedCamera(const int index) const;
    void setActiveIndex(const int val);

    const IECameraScript* getScript(const int index) const;
    unsigned long long getCameraId(const int index) const;

    void setScript(const int index, const IECameraScript& val);
    void setCameraId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

