#pragma once

#include "IEBaseRigidbody.h"

class IESphereRigidbody : public IEBaseRigidbody
{
    float radius;

public:
    IESphereRigidbody(physx::PxPhysics* p,
                      physx::PxMaterial* m);
    IESphereRigidbody(physx::PxPhysics* p,
                   physx::PxMaterial* m,
                   RigidbodyType type,
                   const int id,
                   const float r,
                   const float d = 0.0f,
                   const float st = 0.0f);
    ~IESphereRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

