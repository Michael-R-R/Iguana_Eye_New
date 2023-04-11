#pragma once

#include "IEBaseRigidbody.h"

class IECapsuleRigidbody : public IEBaseRigidbody
{
    float radius;
    float halfHeight;

public:
    IECapsuleRigidbody();
    IECapsuleRigidbody(RigidbodyType type,
                       const int id,
                       const float r, const float hh,
                       const float d = 0.0f,
                       const float st = 0.0f);
    ~IECapsuleRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

