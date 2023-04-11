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
    physx::PxRigidActor* rigidActor;

    ColliderShape colliderShape;
    int attachedId;

public:
    IEBaseCollider();
    IEBaseCollider(ColliderShape shape,
                   const int id);
    ~IEBaseCollider();

    virtual void create(const physx::PxTransform&) {}

    void release();
    void setIsTrigger(const bool val);

    physx::PxVec3 getGlobalPos() const;
    physx::PxQuat getGlobalQuat() const;
    physx::PxRigidActor* getActor() const { return rigidActor; }
    ColliderShape getShape() const { return colliderShape; }

protected:
    void create(const physx::PxTransform& t, const physx::PxGeometry& g);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

