#pragma once

#include <memory>
#include <vector>
#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IERigidBody.h"

class IEGame;
class IEPhysicsEngine;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        std::vector<std::unique_ptr<IERigidBody>> rigidbody;

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
    IEPhysicsEngine* engine;

public:
    IEECSRigidbody3DSystem(IEGame& game);
    ~IEECSRigidbody3DSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void play();
    void stop();

    void wakeup(const int index);
    void putToSleep(const int index);
    void release(const int index);

    IERigidBody* getRigidbody(const int index) const;
    void setRigidbody(const int index, const std::unique_ptr<IERigidBody> val);

private slots:
    void activateRigidbody(const IEEntity& entity);
    void deactivateRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

