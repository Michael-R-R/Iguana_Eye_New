#include "IEBoxRigidBody.h"

IEBoxRigidbody::IEBoxRigidbody(QObject* parent) :
    IEBaseRigidbody(RigidbodyType::None, RigidbodyShape::Box, 0, 0.0f, 0.0f, parent),
    extentX(1.0f), extentY(1.0f), extentZ(1.0f)
{

}

IEBoxRigidbody::IEBoxRigidbody(RigidbodyType type,
                               const int id,
                               const float x, const float y, const float z,
                               const float d, const float st,
                               QObject* parent) :
    IEBaseRigidbody(type, RigidbodyShape::Box, id, d, st, parent),
    extentX(x), extentY(y), extentZ(z)
{

}

IEBoxRigidbody::~IEBoxRigidbody()
{

}

void IEBoxRigidbody::create(const physx::PxTransform& t)
{
    physx::PxBoxGeometry g(extentX, extentY, extentZ);

    IEBaseRigidbody::create(t, g);
}

QDataStream& IEBoxRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseRigidbody::serialize(out, obj);

    const IEBoxRigidbody& body = static_cast<const IEBoxRigidbody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;
    out << body.extentX << body.extentY << body.extentZ;

    return out;
}

QDataStream& IEBoxRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody::deserialize(in, obj);

    IEBoxRigidbody& body = static_cast<IEBoxRigidbody&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> body.extentX >> body.extentY >> body.extentZ;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    body.create(t);

    return in;
}

