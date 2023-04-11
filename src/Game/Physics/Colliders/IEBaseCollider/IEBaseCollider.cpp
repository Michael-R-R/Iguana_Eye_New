#include "IEBaseCollider.h"
#include "IEPhysicsEngine.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBaseCollider::IEBaseCollider() :
    rigidActor(nullptr),
    colliderShape(ColliderShape::None), attachedId(0)
{

}

IEBaseCollider::IEBaseCollider(ColliderShape shape,
                               const int id) :
    rigidActor(nullptr),
    colliderShape(shape), attachedId(id)
{

}

IEBaseCollider::~IEBaseCollider()
{
    if(rigidActor)
        rigidActor->release();
}

void IEBaseCollider::release()
{
    if(!rigidActor)
        return;

    rigidActor->release();
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

physx::PxVec3 IEBaseCollider::getGlobalPos() const
{
    if(!rigidActor)
        return physx::PxVec3();

    return rigidActor->getGlobalPose().p;
}

physx::PxQuat IEBaseCollider::getGlobalQuat() const
{
    if(!rigidActor)
        return physx::PxQuat();

    return rigidActor->getGlobalPose().q;
}

void IEBaseCollider::create(const physx::PxTransform& t, const physx::PxGeometry& g)
{
    auto* p = IEPhysicsEngine::instance().getPxPhysics();
    auto* m = IEPhysicsEngine::instance().getPxMaterial();

    auto* actor = physx::PxCreateStatic(*p, t, g, *m);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;

    IEPhysicsEngine::instance().addActorToScene(rigidActor);
}

QDataStream& IEBaseCollider::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEBaseCollider& collider = static_cast<const IEBaseCollider&>(obj);

    physx::PxVec3 p = collider.getGlobalPos();
    physx::PxQuat q = collider.getGlobalQuat();

    out << collider.colliderShape << collider.attachedId;
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;

    return out;
}

QDataStream& IEBaseCollider::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseCollider& collider = static_cast<IEBaseCollider&>(obj);

    in >> collider.colliderShape >> collider.attachedId;

    return in;
}
