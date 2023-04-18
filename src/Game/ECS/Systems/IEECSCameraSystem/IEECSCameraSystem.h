#pragma once

#include <QSharedPointer>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"
#include "IECameraScript.h"

class IECamera;
class ECSOnUpdateEvent;

class IEECSCameraSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> cameraId;
        QVector<QSharedPointer<IECameraScript>> cameraScript;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.cameraId;
            out << (int)data.cameraScript.size();

            foreach(auto& i, data.cameraScript)
            {
                out << *i;
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            data.cameraScript.clear();

            int size = 0;
            in >> data.entity >> data.cameraId >> size;

            for(int i = 0; i < size; i++)
            {
                auto script = QSharedPointer<IECameraScript>::create();

                in >> *script;

                data.cameraScript.append(script);
            }

            return in;
        }
    };

    Data data;

    int activeIndex;

public:
    IEECSCameraSystem(QObject* parent = nullptr);
    ~IEECSCameraSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent& event) override;
    void initalize() override;

    int getActiveIndex() const;
    IEEntity getActiveEntity() const;
    IECamera* getActiveCamera() const;
    IECamera* getAttachedCamera(const int index) const;
    void setActiveIndex(const int val);

    const QSharedPointer<IECameraScript> getScript(const int index) const;
    unsigned long long getCameraId(const int index) const;

    void setScript(const int index, const QSharedPointer<IECameraScript> val);
    void setCameraId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

