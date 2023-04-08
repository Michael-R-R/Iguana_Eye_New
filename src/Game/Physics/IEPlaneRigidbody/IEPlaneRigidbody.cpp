#include "IEPlaneRigidbody.h"

IEPlaneRigidbody::IEPlaneRigidbody(physx::PxPhysics* p,
                                   physx::PxMaterial* m) :
    IERigidbody(p, m, RigidbodyType::None, RigidbodyShape::Plane, 0)
{

}

IEPlaneRigidbody::IEPlaneRigidbody(physx::PxPhysics* p,
                                   physx::PxMaterial* m,
                                   RigidbodyType type,
                                   const int id,
                                   const float d, const float st) :
    IERigidbody(p, m, type, RigidbodyShape::Plane, id, d, st)
{

}

IEPlaneRigidbody::~IEPlaneRigidbody()
{

}

void IEPlaneRigidbody::create(const physx::PxTransform& t)
{
    physx::PxPlaneGeometry g;

    IERigidbody::create(t, g);
}

QDataStream& IEPlaneRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    return IERigidbody::serialize(out, obj);
}

QDataStream& IEPlaneRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IERigidbody::deserialize(in, obj);

    IEPlaneRigidbody& body = static_cast<IEPlaneRigidbody&>(obj);

    float px = 0.0f, py = 0.0f, pz = 0.0f;
    float qx = 0.0f, qy = 0.0f, qz = 0.0f, qw = 0.0f;
    in >> px >> py >> pz;
    in >> qx >> qy >> qz >> qw;

    physx::PxTransform p(px, py, pz);
    physx::PxTransform q(physx::PxQuat(qx, qy, qz, qw));
    physx::PxTransform t = p * q;
    body.create(t);

    return in;
}

