#pragma once

#include <QVector>

#include "IEECSSystem.h"
#include "IEBaseCollider.h"
#include "IEBoxCollider.h"
#include "IESphereCollider.h"
#include "IECapsuleCollider.h"

class IEGame;

class IEECSColliderSystem : public IEECSSystem
{
    struct Data : public IEObject
    {
        QVector<IEEntity> entity;
        QVector<IEBaseCollider*> collider;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << (int)data.collider.size();

            for(auto& i : data.collider)
            {
                out << i->getShape() << *i;
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            int size = 0;

            in >> data.entity >> size;

            IEBaseCollider::ColliderShape shape;
            IEBaseCollider* collider = nullptr;

            data.collider.clear();
            for(int i = 0; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IEBaseCollider::ColliderShape::None: { collider = new IEBaseCollider(&data); break; }
                case IEBaseCollider::ColliderShape::Box: { collider = new IEBoxCollider(&data); break; }
                case IEBaseCollider::ColliderShape::Sphere: { collider = new IESphereCollider(&data); break; }
                case IEBaseCollider::ColliderShape::Capsule: { collider = new IECapsuleCollider(&data); break; }
                }

                in >> *collider;

                data.collider.push_back(collider);
            }

            return in;
        }
    };

    Data data;

public:
    IEECSColliderSystem(QObject* parent = nullptr);
    ~IEECSColliderSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void shutdown(const IEGame& game) override;
    void onDeserialize(const IEGame& game) override;

    IEBaseCollider* getCollider(const int index) const;
    void setCollider(const int index, IEBaseCollider* val);
    void setIsTrigger(const int index, const bool val);
    void removeCollider(const int index);
    void removeAll();

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

