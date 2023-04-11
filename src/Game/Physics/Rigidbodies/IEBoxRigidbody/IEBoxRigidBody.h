#pragma once

#include "IEBaseRigidbody.h"

class IEBoxRigidbody : public IEBaseRigidbody
{
    float extentX, extentY, extentZ;

public:
    IEBoxRigidbody(physx::PxPhysics* p,
                   physx::PxMaterial* m);
    IEBoxRigidbody(physx::PxPhysics* p,
                   physx::PxMaterial* m,
                   RigidbodyType type,
                   const int id,
                   const float x, const float y, const float z,
                   const float d = 0.0f,
                   const float st = 0.0f);
    IEBoxRigidbody(const IEBoxRigidbody&) = delete;
    ~IEBoxRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

