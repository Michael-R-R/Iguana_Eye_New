#include "IEBoxCollider.h"

IEBoxCollider::IEBoxCollider() :
    IEBaseCollider(nullptr, nullptr, ColliderShape::Box, 0),
    extentX(0.0f), extentY(0.0f), extentZ(0.0f)
{

}

IEBoxCollider::IEBoxCollider(physx::PxPhysics* p, physx::PxMaterial* m,
                             const int id,
                             const float x, const float y, const float z) :
    IEBaseCollider(p, m, ColliderShape::Box, id),
    extentX(x), extentY(y), extentZ(z)
{

}

IEBoxCollider::~IEBoxCollider()
{

}

void IEBoxCollider::create(const physx::PxTransform& t)
{
    const physx::PxBoxGeometry& box = physx::PxBoxGeometry(extentX, extentY, extentZ);

    IEBaseCollider::create(t, box);
}
