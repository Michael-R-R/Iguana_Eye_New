#pragma once

#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IERigidBody.h"

class IEGame;

// TODO finish implementing
class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

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

public:
    IEECSRigidbody3DSystem(IEGame& game);
    ~IEECSRigidbody3DSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void wakeup(const int index);
    void putToSleep(const int index);
    void release(const int index);

    const IERigidBody& getRigidbody(const int index) const;
    void setRigidbody(const int index, const IERigidBody& val);

private slots:
    void activateRigidbody(const IEEntity& entity);
    void deactivateRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

