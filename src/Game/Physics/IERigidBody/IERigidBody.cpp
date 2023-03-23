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
    this->createAsDynamic(physics, material, t, geometry, density, sleepThresh, isKinematic);
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
    auto* obj = physx::PxCreateStatic(physics, t, geometry, material);

    rigidActor = obj;
    bodyType = BodyType::Static;
}

void IERigidBody::createAsDynamic(physx::PxPhysics& physics,
                                  physx::PxMaterial& material,
                                  const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry,
                                  const float density,
                                  const float sleepThresh,
                                  bool isKinematic)
{
    auto* obj = physx::PxCreateDynamic(physics, t, geometry, material, density);
    obj->setSleepThreshold(sleepThresh);
    obj->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, isKinematic);

    rigidActor = obj;
    bodyType = (isKinematic) ? BodyType::Kinematic : BodyType::Dynamic;
}
