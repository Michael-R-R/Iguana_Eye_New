#pragma once

#include "Serializable.h"
#include "PxRigidActor.h"
#include "PxRigidStatic.h"
#include "PxRigidDynamic.h"

class IERigidBody : public Serializable
{
public:
    enum class RigidbodyType
    {
        None, Static, Dynamic, Kinematic
    };

    enum class RigidbodyShape
    {
        None, Box, Sphere, Capsule
    };

protected:
    // DOES NOT OWN THESE POINTERS
    physx::PxPhysics* physics;
    physx::PxMaterial* material;
    physx::PxRigidActor* rigidActor;

    RigidbodyType rigidbodyType;
    RigidbodyShape rigidbodyShape;
    int attachedId;
    float density;
    float sleepThreshold;

public:
    IERigidBody();
    IERigidBody(physx::PxPhysics* p,
                physx::PxMaterial* m,
                RigidbodyType type,
                RigidbodyShape shape,
                const int id,
                const float d = 0.0f,
                const float st = 0.0f);
    IERigidBody(const IERigidBody& other);
    ~IERigidBody();

    virtual void create(const physx::PxTransform&) {}

    bool wakeup();
    bool putToSleep();
    void release();

    bool is(RigidbodyType type) const { return (this->rigidbodyType == type); }
    physx::PxRigidActor* getActor() const { return rigidActor; }
    physx::PxRigidStatic* getStatic() const { return static_cast<physx::PxRigidStatic*>(rigidActor); }
    physx::PxRigidDynamic* getDynamic() const { return static_cast<physx::PxRigidDynamic*>(rigidActor); }
    physx::PxVec3 getGlobalPos() const { return rigidActor->getGlobalPose().p; }
    physx::PxQuat getGlobalQuat() const { return rigidActor->getGlobalPose().q; }
    RigidbodyType getRigidbodyType() const { return rigidbodyType; }
    RigidbodyShape getRigidbodyShape() const { return rigidbodyShape; }

protected:
    void createAsStatic(const physx::PxTransform& t,
                        const physx::PxGeometry& geometry);

    void createAsDynamic(const physx::PxTransform& t,
                         const physx::PxGeometry& geometry);

    void createAsKinematic(const physx::PxTransform& t,
                           const physx::PxGeometry& geometry);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

