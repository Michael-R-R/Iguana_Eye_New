#pragma once

#include <memory>
#include <vector>
#include <QVector>
#include <QSet>

#include "IEECSSystem.h"
#include "IERigidBody.h"
#include "IEBoxRigidBody.h"
#include "IEPhysicsEngine.h"

class IEGame;

class IEECSRigidbody3DSystem : public IEECSSystem
{
    Q_OBJECT

    struct Data
    {
        QVector<IEEntity> entity;
        std::vector<std::unique_ptr<IERigidBody>> rigidbody;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << (int)data.rigidbody.size();

            for(int i = 0; i < data.rigidbody.size(); i++)
            {
                if(!data.rigidbody[i])
                    out << IERigidBody::RigidbodyShape::None;
                else
                    out << data.rigidbody[i]->getRigidbodyShape() << *data.rigidbody[i];
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            int size = 0;

            data.rigidbody.clear();

            in >> data.entity >> size;

            IERigidBody::RigidbodyShape shape;
            std::unique_ptr<IERigidBody> rigidbody = nullptr;
            auto& engine = IEPhysicsEngine::instance();
            auto* pxPhysics = engine.getPxPhysics();
            auto* pxMaterial = engine.getDefaultPxMaterial();

            for(int i = 0; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IERigidBody::RigidbodyShape::None: { rigidbody = nullptr; break; }
                case IERigidBody::RigidbodyShape::Box: { rigidbody = std::make_unique<IEBoxRigidBody>(pxPhysics, pxMaterial); break; }
                case IERigidBody::RigidbodyShape::Sphere: { break; }
                case IERigidBody::RigidbodyShape::Capsule: { break; }
                default: { rigidbody = nullptr; break; }
                }

                if(rigidbody)
                    in >> *rigidbody;

                data.rigidbody.push_back(std::move(rigidbody));
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

    IERigidBody* getRigidbody(const int index) const;
    void setRigidbody(const int index, const std::unique_ptr<IERigidBody> val);

private slots:
    void activateRigidbody(const IEEntity& entity);
    void deactivateRigidbody(const IEEntity& entity);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

