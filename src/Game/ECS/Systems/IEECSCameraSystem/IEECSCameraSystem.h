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
        QVector<unsigned long long> cameraId;
        QVector<IECameraScript> cameraScript;

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

    void initalizeAllScripts(sol::state& lua);
    void startAllScripts();

    bool initalizeScript(const int index, sol::state& lua);
    void startScript(const int index);

    int getActiveIndex() const;
    IEEntity getActiveEntity() const;
    IECamera* getActiveCamera() const;
    IECamera* getAttachedCamera(const int index) const;
    void setActiveIndex(const int val);

    unsigned long long getCameraId(const int index) const;
    IECameraScript* getScript(const int index);

    void setCameraId(const int index, const unsigned long long val);
    void setScript(const int index, const IECameraScript& val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

