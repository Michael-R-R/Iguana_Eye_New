#include "IECapsuleCollider.h"

IECapsuleCollider::IECapsuleCollider(QObject* parent) :
    IEBaseCollider(ColliderShape::Capsule, 0, parent),
    radius(1.0f), halfHeight(1.0f)
{

}

IECapsuleCollider::IECapsuleCollider(const int id, const float r, const float hh,
                                     QObject* parent) :
    IEBaseCollider(ColliderShape::Capsule, id, parent),
    radius(r), halfHeight(hh)
{

}

IECapsuleCollider::~IECapsuleCollider()
{

}

void IECapsuleCollider::create(const physx::PxTransform& t)
{
    const physx::PxCapsuleGeometry sphere = physx::PxCapsuleGeometry(radius, halfHeight);

    IEBaseCollider::create(t, sphere);
}

QDataStream& IECapsuleCollider::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEBaseCollider::serialize(out, obj);

    const IECapsuleCollider& collider = static_cast<const IECapsuleCollider&>(obj);

    physx::PxVec3 p = collider.getGlobalPos();
    physx::PxQuat q = collider.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;
    out << collider.radius << collider.halfHeight;

    return out;
}

QDataStream& IECapsuleCollider::deserialize(QDataStream& in, IESerializable& obj)
{
    IEBaseCollider::deserialize(in, obj);

    IECapsuleCollider& collider = static_cast<IECapsuleCollider&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> collider.radius << collider.halfHeight;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    collider.create(t);

    return in;
}

