#include "IEBaseCollider.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBaseCollider::IEBaseCollider() :
    physics(nullptr), material(nullptr), rigidActor(nullptr),
    colliderShape(ColliderShape::None), attachedId(0)
{

}

IEBaseCollider::IEBaseCollider(physx::PxPhysics* p,
                               physx::PxMaterial* m,
                               ColliderShape shape,
                               const int id) :
    physics(p), material(m), rigidActor(nullptr),
    colliderShape(shape), attachedId(id)
{

}

IEBaseCollider::~IEBaseCollider()
{
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr; // Manually clean up with release() or let scene clean up
}

void IEBaseCollider::setIsTrigger(const bool val)
{
    if(!rigidActor)
        return;

    physx::PxShape* shape;
    rigidActor->getShapes(&shape, 1);

    shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !val);
    shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, val);
}

void IEBaseCollider::create(const physx::PxTransform& t, const physx::PxGeometry& g)
{
    auto* actor = physx::PxCreateStatic(*physics, t, g, *material);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
}


QDataStream& IEBaseCollider::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEBaseCollider::deserialize(QDataStream& in, Serializable&)
{
    return in;
}
