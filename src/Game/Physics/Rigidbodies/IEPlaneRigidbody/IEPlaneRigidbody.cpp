#include "IEPlaneRigidbody.h"

IEPlaneRigidbody::IEPlaneRigidbody(QObject* parent) :
    IEBaseRigidbody(RigidbodyType::None, RigidbodyShape::Plane, 0, 0.0f, 0.0f, parent)
{

}

IEPlaneRigidbody::IEPlaneRigidbody(RigidbodyType type,
                                   const int id,
                                   const float d, const float st,
                                   QObject* parent) :
    IEBaseRigidbody(type, RigidbodyShape::Plane, id, d, st, parent)
{

}

IEPlaneRigidbody::~IEPlaneRigidbody()
{

}

void IEPlaneRigidbody::create(const physx::PxTransform& t)
{
    physx::PxPlaneGeometry g;

    IEBaseRigidbody::create(t, g);
}

QDataStream& IEPlaneRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBaseRigidbody::serialize(out, obj);

    const IEPlaneRigidbody& body = static_cast<const IEPlaneRigidbody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;

    return out;
}

QDataStream& IEPlaneRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody::deserialize(in, obj);

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

