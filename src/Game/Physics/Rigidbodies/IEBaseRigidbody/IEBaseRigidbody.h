#pragma once

#include "Serializable.h"
#include "PxRigidActor.h"
#include "PxRigidStatic.h"
#include "PxRigidDynamic.h"

class IEBaseRigidbody : public Serializable
{
public:
    enum class RigidbodyType
    {
        None, Static, Dynamic, Kinematic
    };

    enum class RigidbodyShape
    {
        None, Box, Sphere, Capsule, Plane
    };

protected:
    physx::PxRigidActor* rigidActor;

    RigidbodyType rigidbodyType;
    RigidbodyShape rigidbodyShape;
    int attachedId;
    float density;
    float sleepThreshold;

public:
    IEBaseRigidbody();
    IEBaseRigidbody(RigidbodyType type,
                    RigidbodyShape shape,
                    const int id,
                    const float d = 0.0f,
                    const float st = 0.0f);
    IEBaseRigidbody(const IEBaseRigidbody&) = delete;
    virtual ~IEBaseRigidbody();

    virtual void create(const physx::PxTransform&) {}

    bool wakeup();
    bool putToSleep();
    void release();

    physx::PxVec3 getGlobalPos() const;
    physx::PxQuat getGlobalQuat() const;

    bool is(RigidbodyType type) const { return (this->rigidbodyType == type); }
    physx::PxRigidActor* getActor() const { return rigidActor; }
    physx::PxRigidStatic* getStatic() const { return static_cast<physx::PxRigidStatic*>(rigidActor); }
    physx::PxRigidDynamic* getDynamic() const { return static_cast<physx::PxRigidDynamic*>(rigidActor); }
    RigidbodyType getRigidbodyType() const { return rigidbodyType; }
    RigidbodyShape getRigidbodyShape() const { return rigidbodyShape; }

protected:
    void create(const physx::PxTransform& t, const physx::PxGeometry& g);
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

