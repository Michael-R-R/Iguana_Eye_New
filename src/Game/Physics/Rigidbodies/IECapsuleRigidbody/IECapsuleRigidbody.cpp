#include "IECapsuleRigidbody.h"

IECapsuleRigidbody::IECapsuleRigidbody(QObject* parent) :
    IEBaseRigidbody(RigidbodyType::None, RigidbodyShape::Capsule, 0, 0.0f, 0.0f, parent),
    radius(1.0f), halfHeight(1.0f)
{

}

IECapsuleRigidbody::IECapsuleRigidbody(RigidbodyType type,
                                       const int id,
                                       const float r, const float hh,
                                       const float d, const float st,
                                       QObject* parent) :
    IEBaseRigidbody(type, RigidbodyShape::Capsule, id, d, st, parent),
    radius(r), halfHeight(hh)
{

}

IECapsuleRigidbody::~IECapsuleRigidbody()
{

}


void IECapsuleRigidbody::create(const physx::PxTransform& t)
{
    physx::PxCapsuleGeometry g(radius, halfHeight);

    IEBaseRigidbody::create(t, g);
}

QDataStream& IECapsuleRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseRigidbody::serialize(out, obj);

    const IECapsuleRigidbody& body = static_cast<const IECapsuleRigidbody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;
    out << body.radius << body.halfHeight;

    return out;
}

QDataStream& IECapsuleRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody::deserialize(in, obj);

    IECapsuleRigidbody& body = static_cast<IECapsuleRigidbody&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> body.radius >> body.halfHeight;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    body.create(t);

    return in;
}
