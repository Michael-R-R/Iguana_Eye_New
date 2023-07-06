#pragma once

#include "IEBaseRigidbody.h"

class IECapsuleRigidbody : public IEBaseRigidbody
{
    float radius;
    float halfHeight;

public:
    IECapsuleRigidbody(QObject* parent = nullptr);
    IECapsuleRigidbody(RigidbodyType type,
                       const int id,
                       const float r, const float hh,
                       const float d = 0.0f,
                       const float st = 0.0f,
                       QObject* parent = nullptr);
    ~IECapsuleRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

