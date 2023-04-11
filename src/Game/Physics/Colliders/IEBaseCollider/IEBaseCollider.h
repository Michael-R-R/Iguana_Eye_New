#pragma once

#include "Serializable.h"
#include "PxShape.h"
#include "PxRigidActor.h"
#include "PxRigidStatic.h"

class IEBaseCollider : public Serializable
{
public:
    enum class ColliderShape
    {
        None, Box, Sphere, Capsule
    };

protected:
    // DOES NOT OWN THESE POINTERS
    physx::PxPhysics* physics;
    physx::PxMaterial* material;
    physx::PxRigidActor* rigidActor;

    ColliderShape colliderShape;
    int attachedId;

public:
    IEBaseCollider();
    IEBaseCollider(physx::PxPhysics* p,
                   physx::PxMaterial* m,
                   ColliderShape shape,
                   const int id);
    ~IEBaseCollider();

    virtual void create(const physx::PxTransform&) {}

    void setIsTrigger(const bool val);

    physx::PxRigidActor* getActor() const { return rigidActor; }

protected:
    void create(const physx::PxTransform& t, const physx::PxGeometry& g);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

