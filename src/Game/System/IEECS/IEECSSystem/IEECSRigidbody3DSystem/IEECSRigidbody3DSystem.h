#pragma once

#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IEBaseRigidbody.h"
#include "IEBoxRigidBody.h"
#include "IESphereRigidbody.h"
#include "IECapsuleRigidbody.h"
#include "IEPlaneRigidbody.h"

class IEGame;
class IEPhysicsEngine;
class IEECSTransformSystem;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data : public IEObject
    {
        QVector<IEEntity> entity;
        QVector<IEBaseRigidbody*> rigidbody;

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
            int size = 0;
            in >> data.entity >> size;

            IEBaseRigidbody::RigidbodyShape shape;
            IEBaseRigidbody* rigidbody = nullptr;

            data.rigidbody.clear();
            for(int i = 0; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IEBaseRigidbody::RigidbodyShape::None: { rigidbody = new IEBaseRigidbody(&data); break; }
                case IEBaseRigidbody::RigidbodyShape::Box: { rigidbody = new IEBoxRigidbody(&data); break; }
                case IEBaseRigidbody::RigidbodyShape::Sphere: { rigidbody = new IESphereRigidbody(&data); break; }
                case IEBaseRigidbody::RigidbodyShape::Capsule: { rigidbody = new IECapsuleRigidbody(&data); break; }
                case IEBaseRigidbody::RigidbodyShape::Plane: { rigidbody = new IEPlaneRigidbody(&data); break; }
                default: { rigidbody = new IEBaseRigidbody(&data); break; }
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

    IEPhysicsEngine* pEngine;
    IEECSTransformSystem* tSystem;

public:
    IEECSRigidbody3DSystem(QObject* parent = nullptr);
    ~IEECSRigidbody3DSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    void onDeserialize(const IEGame& game) override;
    void onUpdateFrame() override;

    void wakeAll();
    void sleepAll();
    void wakeup(const int index);
    void sleep(const int index);
    void removeRigidbody(const int index);
    void removeAll();

    IEBaseRigidbody* getRigidbody(const int index) const;
    void setRigidbody(const int index, IEBaseRigidbody* val);

private slots:
    void wakeRigidbody(const IEEntity& entity);
    void sleepRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

