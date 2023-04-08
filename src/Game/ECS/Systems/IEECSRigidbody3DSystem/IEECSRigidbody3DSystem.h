#pragma once

#include <QSharedPointer>
#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IERigidBody.h"
#include "IEBoxRigidBody.h"
#include "IESphereRigidbody.h"
#include "IECapsuleRigidbody.h"
#include "IEPlaneRigidbody.h"
#include "IEPhysicsEngine.h"

class IEGame;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QSharedPointer<IERigidbody>> rigidbody;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << (int)data.rigidbody.size();

            for(int i = 1; i < data.rigidbody.size(); i++)
            {
                out << data.rigidbody[i]->getRigidbodyShape() << *data.rigidbody[i];
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            data.rigidbody.clear();
            data.rigidbody.append(QSharedPointer<IERigidbody>::create());

            int size = 0;
            in >> data.entity >> size;

            IERigidbody::RigidbodyShape shape;
            QSharedPointer<IERigidbody> rigidbody = nullptr;
            auto& engine = IEPhysicsEngine::instance();
            auto* pxPhysics = engine.getPxPhysics();
            auto* pxMaterial = engine.getDefaultPxMaterial();

            for(int i = 1; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IERigidbody::RigidbodyShape::None: { rigidbody = QSharedPointer<IERigidbody>::create(); break; }
                case IERigidbody::RigidbodyShape::Box: { rigidbody = QSharedPointer<IEBoxRigidbody>::create(pxPhysics, pxMaterial); break; }
                case IERigidbody::RigidbodyShape::Sphere: { rigidbody = QSharedPointer<IESphereRigidbody>::create(pxPhysics, pxMaterial); break; }
                case IERigidbody::RigidbodyShape::Capsule: { rigidbody = QSharedPointer<IECapsuleRigidbody>::create(pxPhysics, pxMaterial); break; }
                case IERigidbody::RigidbodyShape::Plane: { rigidbody = QSharedPointer<IEPlaneRigidbody>::create(pxPhysics, pxMaterial); break; }
                default: { rigidbody = QSharedPointer<IERigidbody>::create(); break; }
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

    QSharedPointer<IERigidbody> getRigidbody(const int index) const;
    void setRigidbody(const int index, const QSharedPointer<IERigidbody> val);

private slots:
    void activateRigidbody(const IEEntity& entity);
    void deactivateRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

