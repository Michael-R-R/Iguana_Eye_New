#pragma once

#include <QSharedPointer>
#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IEBaseRigidbody.h"
#include "IEBoxRigidBody.h"
#include "IESphereRigidbody.h"
#include "IECapsuleRigidbody.h"
#include "IEPlaneRigidbody.h"

class IEGame;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QSharedPointer<IEBaseRigidbody>> rigidbody;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << (int)data.rigidbody.size();

            for(auto& i : data.rigidbody)
            {
                out << i->getRigidbodyShape() << *i;
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            data.rigidbody.clear();

            int size = 0;
            in >> data.entity >> size;

            IEBaseRigidbody::RigidbodyShape shape;
            QSharedPointer<IEBaseRigidbody> rigidbody = nullptr;

            for(int i = 0; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IEBaseRigidbody::RigidbodyShape::None: { rigidbody = QSharedPointer<IEBaseRigidbody>::create(); break; }
                case IEBaseRigidbody::RigidbodyShape::Box: { rigidbody = QSharedPointer<IEBoxRigidbody>::create(); break; }
                case IEBaseRigidbody::RigidbodyShape::Sphere: { rigidbody = QSharedPointer<IESphereRigidbody>::create(); break; }
                case IEBaseRigidbody::RigidbodyShape::Capsule: { rigidbody = QSharedPointer<IECapsuleRigidbody>::create(); break; }
                case IEBaseRigidbody::RigidbodyShape::Plane: { rigidbody = QSharedPointer<IEPlaneRigidbody>::create(); break; }
                default: { rigidbody = QSharedPointer<IEBaseRigidbody>::create(); break; }
                }

                in >> *rigidbody;

                data.rigidbody.push_back(rigidbody);
            }

            return in;
        }
    };

    Data data;

    QSet<int> awakeBodies;
    QSet<int> sleepingBodies;

public:
    IEECSRigidbody3DSystem();
    ~IEECSRigidbody3DSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void initalize() override;
    void reset() override;

    void wakeup(const int index);
    void putToSleep(const int index);
    void release(const int index);

    QSharedPointer<IEBaseRigidbody> getRigidbody(const int index) const;
    void setRigidbody(const int index, const QSharedPointer<IEBaseRigidbody> val);

private slots:
    void activateRigidbody(const IEEntity& entity);
    void deactivateRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

