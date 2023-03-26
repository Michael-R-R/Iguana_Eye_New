#pragma once

#include <QVector>
#include <QMap>
#include <QSet>
#include <vector>

#include "IEECSSystem.h"
#include "IERigidBody.h"

class IEPhysicsEngine;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<IERigidBody> rigidbody;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity;
            return in;
        }
    };

    Data data;

    QSet<int> awakeBodies;
    QSet<int> sleepingBodies;

    // DOES NOT OWN THIS POINTER
    IEPhysicsEngine* physicsEngine;

public:
    IEECSRigidbody3DSystem();
    ~IEECSRigidbody3DSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void wakeup(const int index);
    void putToSleep(const int index);
    void release(const int index);

    const IERigidBody& getRigidbody(const int index) const;
    void setRigidbody(const int index, const IERigidBody& val);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

