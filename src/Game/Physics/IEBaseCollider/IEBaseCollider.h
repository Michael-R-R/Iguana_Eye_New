#pragma once

#include "PxShape.h"
#include "PxRigidStatic.h"

class IEBaseCollider
{
protected:
    physx::PxShape* shape;
    physx::PxRigidActor* rigidActor;

public:
    IEBaseCollider();
    ~IEBaseCollider();

    void setIsTrigger(const bool val);

    physx::PxShape* getShape() { return shape; }
    physx::PxRigidActor* getActor() { return rigidActor; }

protected:
    virtual void createShape(physx::PxPhysics& physics,
                             physx::PxMaterial& material,
                             const physx::PxGeometry& geometry,
                             const physx::PxTransform& t) = 0;
};

