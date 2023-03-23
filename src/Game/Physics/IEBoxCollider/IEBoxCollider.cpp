#include "IEBoxCollider.h"
#include "PxPhysics.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBoxCollider::IEBoxCollider(physx::PxPhysics& physics,
                             physx::PxMaterial& material,
                             const physx::PxGeometry& geometry,
                             const physx::PxTransform& t,
                             const int attachedId)
{
    IEBoxCollider::createShape(physics, material, geometry, t);
    rigidActor->userData = (void*)(size_t)attachedId;
}

IEBoxCollider::~IEBoxCollider()
{

}

void IEBoxCollider::createShape(physx::PxPhysics& physics,
                                physx::PxMaterial& material,
                                const physx::PxGeometry& geometry,
                                const physx::PxTransform& t)
{
    auto* actor = physx::PxCreateStatic(physics, t, geometry, material);

    shape = physics.createShape(geometry, material);
    rigidActor = actor;
    rigidActor->attachShape(*shape);
}
