#pragma once

#include <memory>
#include <vector>
#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IEPhysicsEngine.h"
#include "IERigidBody.h"
#include "IEBoxRigidBody.h"

class IEGame;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        std::vector<std::unique_ptr<IERigidBody>> rigidbody;

        IEPhysicsEngine* engine;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << (int)data.rigidbody.size();

            for(int i = 1; i < data.rigidbody.size(); i++)
            {
                auto* rigidBody = &(*data.rigidbody[i]);

                out << rigidBody->getRigidbodyShape() << *rigidBody;

                physx::PxVec3 p = rigidBody->getGlobalPos();
                physx::PxQuat q = rigidBody->getGlobalQuat();
                out << p.x << p.y << p.z;
                out << q.x << q.y << q.z << q.w;
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity;

            int size = 0;
            in >> size;

            IERigidBody::RigidbodyShape shape;
            std::unique_ptr<IERigidBody> rigidbody = nullptr;
            auto* pxPhysics = data.engine->getPxPhysics();
            auto* pxMaterial = data.engine->getDefaultPxMaterial();

            data.rigidbody.clear();
            data.rigidbody.push_back(nullptr);

            for(int i = 1; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IERigidBody::RigidbodyShape::None: { break; }
                case IERigidBody::RigidbodyShape::Box: { rigidbody = std::make_unique<IEBoxRigidBody>(pxPhysics, pxMaterial); break; }
                case IERigidBody::RigidbodyShape::Sphere: { break; }
                case IERigidBody::RigidbodyShape::Capsule: { break; }
                default: { break; }
                }

                in >> *rigidbody;

                float px = 0.0f, py = 0.0f, pz = 0.0f;
                float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;

                in >> px >> py >> pz;
                in >> qx >> qy >> qz >> qw;

                physx::PxTransform p(px, py, pz);
                physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
                physx::PxTransform t = p * q;

                rigidbody->create(t);

                data.rigidbody.push_back(std::move(rigidbody));
            }

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
    void play(IEGame& game) override;
    void stop(IEGame& game) override;

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

