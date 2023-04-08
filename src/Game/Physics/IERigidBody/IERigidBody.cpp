#include "IERigidBody.h"
#include "physx/extensions/PxSimpleFactory.h"

IERigidbody::IERigidbody() :
    physics(nullptr),
    material(nullptr),
    rigidActor(nullptr),
    rigidbodyType(RigidbodyType::None),
    rigidbodyShape(RigidbodyShape::None),
    attachedId(0), density(1.0f), sleepThreshold(1.0f)
{

}

IERigidbody::IERigidbody(physx::PxPhysics* p,
                         physx::PxMaterial* m,
                         RigidbodyType type,
                         RigidbodyShape shape,
                         const int id,
                         const float d,
                         const float st) :
    physics(p), material(m), rigidActor(nullptr),
    rigidbodyType(type), rigidbodyShape(shape),
    attachedId(id), density(d), sleepThreshold(st)
{

}

IERigidbody::~IERigidbody()
{
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr; // Manually clean up with release() or let scene clean up
}

bool IERigidbody::wakeup()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->wakeUp();

    return true;
}

bool IERigidbody::putToSleep()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->putToSleep();

    return true;
}

void IERigidbody::release()
{
    rigidActor->release();
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr;
    rigidbodyType = RigidbodyType::None;
    rigidbodyShape = RigidbodyShape::None;
}

void IERigidbody::create(const physx::PxTransform& t, const physx::PxGeometry& g)
{
    switch(rigidbodyType)
    {
    case IERigidbody::RigidbodyType::None: { break; }
    case IERigidbody::RigidbodyType::Static: { createAsStatic(t, g); break; }
    case IERigidbody::RigidbodyType::Dynamic: { createAsDynamic(t, g); break; }
    case IERigidbody::RigidbodyType::Kinematic: { createAsKinematic(t, g); break; }
    default: { break; }
    }
}

void IERigidbody::createAsStatic(const physx::PxTransform& t,
                                 const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateStatic(*physics, t, geometry, *material);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
}

void IERigidbody::createAsDynamic(const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateDynamic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

void IERigidbody::createAsKinematic(const physx::PxTransform& t,
                                    const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateKinematic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

QDataStream& IERigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    const IERigidbody& body = static_cast<const IERigidbody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();

    out << body.rigidbodyType << body.attachedId << body.density << body.sleepThreshold;
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;

    return out;
}

QDataStream& IERigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IERigidbody& body = static_cast<IERigidbody&>(obj);

    in >> body.rigidbodyType >> body.attachedId >> body.density >> body.sleepThreshold;

    return in;
}
