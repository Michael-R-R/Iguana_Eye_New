#include "IEBoxCollider.h"

IEBoxCollider::IEBoxCollider(QObject* parent) :
    IEBaseCollider(ColliderShape::Box, 0, parent),
    extentX(1.0f), extentY(1.0f), extentZ(1.0f)
{

}

IEBoxCollider::IEBoxCollider(const int id,
                             const float x, const float y, const float z,
                             QObject* parent) :
    IEBaseCollider(ColliderShape::Box, id, parent),
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

QDataStream& IEBoxCollider::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseCollider::serialize(out, obj);

    const IEBoxCollider& collider = static_cast<const IEBoxCollider&>(obj);

    physx::PxVec3 p = collider.getGlobalPos();
    physx::PxQuat q = collider.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;
    out << collider.extentX << collider.extentY << collider.extentZ;

    return out;
}

QDataStream& IEBoxCollider::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseCollider::deserialize(in, obj);

    IEBoxCollider& collider = static_cast<IEBoxCollider&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> collider.extentX >> collider.extentY >> collider.extentZ;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    collider.create(t);

    return in;
}
