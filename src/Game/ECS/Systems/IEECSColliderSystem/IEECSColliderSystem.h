#pragma once

#include <QSharedPointer>
#include <QVector>

#include "IEECSSystem.h"
#include "IEBaseCollider.h"
#include "IEBoxCollider.h"
#include "IESphereCollider.h"
#include "IECapsuleCollider.h"

class IEECSColliderSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QSharedPointer<IEBaseCollider>> collider;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity;

            int size = data.collider.size();
            out << size;

            for(auto& i : data.collider)
            {
                out << i->getShape() << *i;
            }

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            data.collider.clear();

            int size = 0;

            in >> data.entity >> size;

            IEBaseCollider::ColliderShape shape;
            QSharedPointer<IEBaseCollider> collider = nullptr;

            for(int i = 0; i < size; i++)
            {
                in >> shape;

                switch(shape)
                {
                case IEBaseCollider::ColliderShape::None: { collider = QSharedPointer<IEBaseCollider>::create(); break; }
                case IEBaseCollider::ColliderShape::Box: { collider = QSharedPointer<IEBoxCollider>::create(); break; }
                case IEBaseCollider::ColliderShape::Sphere: { collider = QSharedPointer<IESphereCollider>::create(); break; }
                case IEBaseCollider::ColliderShape::Capsule: { collider = QSharedPointer<IECapsuleCollider>::create(); break; }
                }

                in >> *collider;

                data.collider.push_back(collider);
            }

            return in;
        }
    };

    Data data;

public:
    IEECSColliderSystem();
    ~IEECSColliderSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void release(const int index);

    QSharedPointer<IEBaseCollider> getCollider(const int index);
    void setCollider(const int index, QSharedPointer<IEBaseCollider> val);
    void setIsTrigger(const int index, const bool val);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

