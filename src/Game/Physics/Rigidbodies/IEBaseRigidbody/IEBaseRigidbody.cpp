#include "IEBaseRigidbody.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBaseRigidbody::IEBaseRigidbody() :
    physics(nullptr),
    material(nullptr),
    rigidActor(nullptr),
    rigidbodyType(RigidbodyType::None),
    rigidbodyShape(RigidbodyShape::None),
    attachedId(0), density(1.0f), sleepThreshold(1.0f)
{

}

IEBaseRigidbody::IEBaseRigidbody(physx::PxPhysics* p,
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

IEBaseRigidbody::~IEBaseRigidbody()
{
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr; // Manually clean up with release() or let scene clean up
}

bool IEBaseRigidbody::wakeup()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->wakeUp();

    return true;
}

bool IEBaseRigidbody::putToSleep()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->putToSleep();

    return true;
}

void IEBaseRigidbody::release()
{
    rigidActor->release();
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr;
    rigidbodyType = RigidbodyType::None;
    rigidbodyShape = RigidbodyShape::None;
}

void IEBaseRigidbody::create(const physx::PxTransform& t, const physx::PxGeometry& g)
{
    switch(rigidbodyType)
    {
    case IEBaseRigidbody::RigidbodyType::None: { break; }
    case IEBaseRigidbody::RigidbodyType::Static: { createAsStatic(t, g); break; }
    case IEBaseRigidbody::RigidbodyType::Dynamic: { createAsDynamic(t, g); break; }
    case IEBaseRigidbody::RigidbodyType::Kinematic: { createAsKinematic(t, g); break; }
    default: { break; }
    }
}

void IEBaseRigidbody::createAsStatic(const physx::PxTransform& t,
                                 const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateStatic(*physics, t, geometry, *material);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
}

void IEBaseRigidbody::createAsDynamic(const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateDynamic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

void IEBaseRigidbody::createAsKinematic(const physx::PxTransform& t,
                                    const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateKinematic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

QDataStream& IEBaseRigidbody::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEBaseRigidbody& body = static_cast<const IEBaseRigidbody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();

    out << body.rigidbodyType << body.attachedId << body.density << body.sleepThreshold;
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;

    return out;
}

QDataStream& IEBaseRigidbody::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseRigidbody& body = static_cast<IEBaseRigidbody&>(obj);

    in >> body.rigidbodyType >> body.attachedId >> body.density >> body.sleepThreshold;

    return in;
}
