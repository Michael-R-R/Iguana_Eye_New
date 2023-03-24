#include "IEBoxCollider.h"
#include "PxPhysics.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBoxCollider::IEBoxCollider(physx::PxPhysics& physics,
                             physx::PxMaterial& material,
                             const physx::PxBoxGeometry& box,
                             const physx::PxTransform& t,
                             const int attachedId)
{
    IEBoxCollider::createShape(physics, material, box, t);
    rigidActor->userData = (void*)(size_t)attachedId;
}

IEBoxCollider::~IEBoxCollider()
{

}

void IEBoxCollider::createShape(physx::PxPhysics& physics,
                                physx::PxMaterial& material,
                                const physx::PxGeometry& box,
                                const physx::PxTransform& t)
{
    physx::PxRigidStatic* actor = physx::PxCreateStatic(physics, t, box, material);

    rigidActor = actor;
}
