#pragma once

#include "PxRigidActor.h"
#include "PxRigidStatic.h"
#include "PxRigidDynamic.h"

class IERigidBody
{
public:
    enum class BodyType
    {
        Static, Dynamic, Kinematic
    };

private:
    physx::PxRigidActor* rigidActor;
    BodyType bodyType;

public:
    IERigidBody(physx::PxPhysics& physics,
                physx::PxMaterial& material,
                const physx::PxTransform& t,
                const physx::PxGeometry& geometry,
                const int attachedId);

    IERigidBody(physx::PxPhysics& physics,
                physx::PxMaterial& material,
                const physx::PxTransform& t,
                const physx::PxGeometry& geometry,
                const float density,
                const float sleepThresh,
                const int attachedId,
                bool isKinematic = false);

    ~IERigidBody();

    bool is(BodyType type) { return (this->bodyType == type); }
    physx::PxRigidActor* getActor() { return rigidActor; }
    physx::PxRigidStatic* getStatic() { return static_cast<physx::PxRigidStatic*>(rigidActor); }
    physx::PxRigidDynamic* getDynamic() { return static_cast<physx::PxRigidDynamic*>(rigidActor); }
    BodyType getBodyType() { return bodyType; }

private:
    void createAsStatic(physx::PxPhysics& physics,
                        physx::PxMaterial& material,
                        const physx::PxTransform& t,
                        const physx::PxGeometry& geometry);

    void createAsDynamic(physx::PxPhysics& physics,
                         physx::PxMaterial& material,
                         const physx::PxTransform& t,
                         const physx::PxGeometry& geometry,
                         const float density,
                         const float sleepThresh);

    void createAsKinematic(physx::PxPhysics& physics,
                           physx::PxMaterial& material,
                           const physx::PxTransform& t,
                           const physx::PxGeometry& geometry,
                           const float density,
                           const float sleepThresh);
};

