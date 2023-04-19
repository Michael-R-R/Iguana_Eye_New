#pragma once

#include "IEBaseCollider.h"

class IECapsuleCollider : public IEBaseCollider
{
    float radius;
    float halfHeight;

public:
    IECapsuleCollider(QObject* parent = nullptr);
    IECapsuleCollider(const int id, const float r, const float hh,
                      QObject* parent = nullptr);
    IECapsuleCollider(const IECapsuleCollider&) = delete;
    ~IECapsuleCollider();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

