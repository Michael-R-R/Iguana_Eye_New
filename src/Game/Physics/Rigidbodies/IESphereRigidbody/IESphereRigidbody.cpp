#include "IESphereRigidbody.h"

IESphereRigidbody::IESphereRigidbody(physx::PxPhysics* p,
                                     physx::PxMaterial* m) :
    IEBaseRigidbody(p, m, RigidbodyType::None, RigidbodyShape::Sphere, 0),
    radius(1.0f)
{

}

IESphereRigidbody::IESphereRigidbody(physx::PxPhysics* p,
                                     physx::PxMaterial* m,
                                     RigidbodyType type,
                                     const int id,
                                     const float r,
                                     const float d, const float st) :
    IEBaseRigidbody(p, m, type, RigidbodyShape::Sphere, id, d, st),
    radius(r)
{

}

IESphereRigidbody::~IESphereRigidbody()
{

}

void IESphereRigidbody::create(const physx::PxTransform& t)
{
    physx::PxSphereGeometry g(radius);

    IEBaseRigidbody::create(t, g);
}

QDataStream& IESphereRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseRigidbody::serialize(out, obj);

    const IESphereRigidbody& body = static_cast<const IESphereRigidbody&>(obj);

    out << body.radius;

    return out;
}

QDataStream& IESphereRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody::deserialize(in, obj);

    IESphereRigidbody& body = static_cast<IESphereRigidbody&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;
    in >> body.radius;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    body.create(t);

    return in;
}
