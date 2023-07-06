#pragma once

#include "IEObject.h"
#include "PxShape.h"
#include "PxRigidActor.h"
#include "PxRigidStatic.h"

class IEBaseCollider : public IEObject
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
    IEBaseCollider(QObject* parent = nullptr);
    IEBaseCollider(ColliderShape shape,
                   const int id,
                   QObject* parent = nullptr);
    virtual ~IEBaseCollider();

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
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

