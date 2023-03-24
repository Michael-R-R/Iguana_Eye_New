#include "IERigidBody.h"
#include "physx/extensions/PxSimpleFactory.h"

IERigidBody::IERigidBody(physx::PxPhysics& physics,
                         physx::PxMaterial& material,
                         const physx::PxTransform& t,
                         const physx::PxGeometry& geometry,
                         const int attachedId)
{
    this->createAsStatic(physics, material, t, geometry);
    rigidActor->userData = (void*)(size_t)attachedId;
}

IERigidBody::IERigidBody(physx::PxPhysics& physics,
                         physx::PxMaterial& material,
                         const physx::PxTransform& t,
                         const physx::PxGeometry& geometry,
                         const float density,
                         const float sleepThresh,
                         const int attachedId,
                         bool isKinematic)
{
    if(isKinematic)
        this->createAsKinematic(physics, material, t, geometry, density, sleepThresh);
    else
        this->createAsDynamic(physics, material, t, geometry, density, sleepThresh);

    rigidActor->userData = (void*)(size_t)attachedId;
}

IERigidBody::~IERigidBody()
{
    // Manually clean up or let scene clean up
    rigidActor = nullptr;
}

void IERigidBody::createAsStatic(physx::PxPhysics& physics,
                                 physx::PxMaterial& material,
                                 const physx::PxTransform& t,
                                 const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateStatic(physics, t, geometry, material);

    rigidActor = actor;
    bodyType = BodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
}

void IERigidBody::createAsDynamic(physx::PxPhysics& physics,
                                  physx::PxMaterial& material,
                                  const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry,
                                  const float density,
                                  const float sleepThresh)
{
    auto* actor = physx::PxCreateDynamic(physics, t, geometry, material, density);
    actor->setSleepThreshold(sleepThresh);

    rigidActor = actor;
    bodyType = BodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

void IERigidBody::createAsKinematic(physx::PxPhysics& physics,
                                    physx::PxMaterial& material,
                                    const physx::PxTransform& t,
                                    const physx::PxGeometry& geometry,
                                    const float density,
                                    const float sleepThresh)
{
    auto* actor = physx::PxCreateKinematic(physics, t, geometry, material, density);
    actor->setSleepThreshold(sleepThresh);

    rigidActor = actor;
    bodyType = BodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}
