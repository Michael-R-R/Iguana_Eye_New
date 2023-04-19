#include "IESphereCollider.h"

IESphereCollider::IESphereCollider(QObject* parent) :
    IEBaseCollider(ColliderShape::Sphere, 0, parent),
    radius(1.0f)
{

}

IESphereCollider::IESphereCollider(const int id, const float r, QObject* parent) :
    IEBaseCollider(ColliderShape::Sphere, id, parent),
    radius(r)
{

}

IESphereCollider::~IESphereCollider()
{

}

void IESphereCollider::create(const physx::PxTransform& t)
{
    const physx::PxSphereGeometry sphere = physx::PxSphereGeometry(radius);

    IEBaseCollider::create(t, sphere);
}

QDataStream& IESphereCollider::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseCollider::serialize(out, obj);

    const IESphereCollider& collider = static_cast<const IESphereCollider&>(obj);

    physx::PxVec3 p = collider.getGlobalPos();
    physx::PxQuat q = collider.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;
    out << collider.radius;

    return out;
}

QDataStream& IESphereCollider::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseCollider::deserialize(in, obj);

    IESphereCollider& collider = static_cast<IESphereCollider&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> collider.radius;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    collider.create(t);

    return in;
}


