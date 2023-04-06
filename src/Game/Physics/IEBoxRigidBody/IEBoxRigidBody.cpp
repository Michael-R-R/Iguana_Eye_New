#include "IEBoxRigidBody.h"

IEBoxRigidBody::IEBoxRigidBody() :
    IERigidBody()
{

}

IEBoxRigidBody::IEBoxRigidBody(physx::PxPhysics* p, physx::PxMaterial* m) :
    IERigidBody(p, m, RigidbodyType::None, RigidbodyShape::Box, 0)
{

}

IEBoxRigidBody::IEBoxRigidBody(physx::PxPhysics* p,
                               physx::PxMaterial* m,
                               RigidbodyType type,
                               const int id,
                               const float x, const float y, const float z,
                               const float d, const float st) :
    IERigidBody(p, m, type, RigidbodyShape::Box, id, d, st),
    extentX(x), extentY(y), extentZ(z)
{

}

IEBoxRigidBody::~IEBoxRigidBody()
{

}

void IEBoxRigidBody::create(const physx::PxTransform& t)
{
    physx::PxBoxGeometry g(extentX, extentY, extentZ);

    switch(rigidbodyType)
    {
    case IERigidBody::RigidbodyType::None: { break; }
    case IERigidBody::RigidbodyType::Static: { createAsStatic(t, g); break; }
    case IERigidBody::RigidbodyType::Dynamic: { createAsDynamic(t, g); break; }
    case IERigidBody::RigidbodyType::Kinematic: { createAsKinematic(t, g); break; }
    default: { break; }
    }
}

QDataStream& IEBoxRigidBody::serialize(QDataStream& out, const Serializable& obj) const
{
    IERigidBody::serialize(out, obj);

    const IEBoxRigidBody& body = static_cast<const IEBoxRigidBody&>(obj);

    out << body.extentX << body.extentY << body.extentZ;

    return out;
}

QDataStream& IEBoxRigidBody::deserialize(QDataStream& in, Serializable& obj)
{
    IERigidBody::deserialize(in, obj);

    IEBoxRigidBody& body = static_cast<IEBoxRigidBody&>(obj);

    in >> body.extentX >> body.extentY >> body.extentZ;

    return in;
}

