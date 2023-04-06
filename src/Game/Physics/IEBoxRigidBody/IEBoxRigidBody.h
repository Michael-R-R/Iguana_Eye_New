#pragma once

#include "IERigidBody.h"

class IEBoxRigidBody : public IERigidBody
{
    float extentX, extentY, extentZ;

public:
    IEBoxRigidBody();
    IEBoxRigidBody(physx::PxPhysics* p,
                   physx::PxMaterial* m);
    IEBoxRigidBody(physx::PxPhysics* p,
                   physx::PxMaterial* m,
                   RigidbodyType type,
                   const int id,
                   const float x, const float y, const float z,
                   const float d = 0.0f,
                   const float st = 0.0f);
    ~IEBoxRigidBody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

