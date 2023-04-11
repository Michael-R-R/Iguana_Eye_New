#include "IECapsuleRigidbody.h"
#include "IEPhysicsEngine.h"

IECapsuleRigidbody::IECapsuleRigidbody() :
    IEBaseRigidbody(nullptr, nullptr, RigidbodyType::None, RigidbodyShape::Capsule, 0),
    radius(1.0f), halfHeight(1.0f)
{

}

IECapsuleRigidbody::IECapsuleRigidbody(physx::PxPhysics* p,
                                       physx::PxMaterial* m,
                                       RigidbodyType type,
                                       const int id,
                                       const float r, const float hh,
                                       const float d, const float st) :
    IEBaseRigidbody(p, m, type, RigidbodyShape::Capsule, id, d, st),
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

    out << body.radius << body.halfHeight;

    return out;
}

QDataStream& IECapsuleRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody::deserialize(in, obj);

    IECapsuleRigidbody& body = static_cast<IECapsuleRigidbody&>(obj);

    body.physics = IEPhysicsEngine::instance().getPxPhysics();
    body.material = IEPhysicsEngine::instance().getDefaultPxMaterial();

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
