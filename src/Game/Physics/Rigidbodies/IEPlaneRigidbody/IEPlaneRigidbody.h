#pragma once

#include "IEBaseRigidbody.h"

class IEPlaneRigidbody : public IEBaseRigidbody
{

public:
    IEPlaneRigidbody(physx::PxPhysics* p,
                     physx::PxMaterial* m);
    IEPlaneRigidbody(physx::PxPhysics* p,
                     physx::PxMaterial* m,
                     RigidbodyType type,
                     const int id,
                     const float d = 0.0f,
                     const float st = 0.0f);
    ~IEPlaneRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

