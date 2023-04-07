#include "IERigidBody.h"
#include "physx/extensions/PxSimpleFactory.h"

IERigidBody::IERigidBody() :
    physics(nullptr),
    material(nullptr),
    rigidActor(nullptr),
    rigidbodyType(RigidbodyType::None),
    rigidbodyShape(RigidbodyShape::None),
    attachedId(0), density(0.0f), sleepThreshold(0.0f)
{

}

IERigidBody::IERigidBody(physx::PxPhysics* p,
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

IERigidBody::IERigidBody(const IERigidBody& other) :
    physics(other.physics), material(other.material), rigidActor(other.rigidActor),
    rigidbodyType(other.rigidbodyType), rigidbodyShape(other.rigidbodyShape),
    attachedId(other.attachedId), density(other.density), sleepThreshold(other.sleepThreshold)
{

}

IERigidBody::~IERigidBody()
{
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr; // Manually clean up with release() or let scene clean up
}

bool IERigidBody::wakeup()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->wakeUp();

    return true;
}

bool IERigidBody::putToSleep()
{
    if(!rigidActor)
        return false;

    if(!is(RigidbodyType::Dynamic) || !is(RigidbodyType::Kinematic))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->putToSleep();

    return true;
}

void IERigidBody::release()
{
    rigidActor->release();
    physics = nullptr;
    material = nullptr;
    rigidActor = nullptr;
    rigidbodyType = RigidbodyType::None;
    rigidbodyShape = RigidbodyShape::None;
}

void IERigidBody::createAsStatic(const physx::PxTransform& t,
                                 const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateStatic(*physics, t, geometry, *material);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
}

void IERigidBody::createAsDynamic(const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateDynamic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

void IERigidBody::createAsKinematic(const physx::PxTransform& t,
                                    const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateKinematic(*physics, t, geometry, *material, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

QDataStream& IERigidBody::serialize(QDataStream& out, const Serializable& obj) const
{
    const IERigidBody& body = static_cast<const IERigidBody&>(obj);

    physx::PxVec3 p = body.getGlobalPos();
    physx::PxQuat q = body.getGlobalQuat();

    out << body.rigidbodyType << body.attachedId << body.density << body.sleepThreshold;
    out << p.x << p.y << p.z;
    out << q.x << q.y << q.z << q.w;

    return out;
}

QDataStream& IERigidBody::deserialize(QDataStream& in, Serializable& obj)
{
    IERigidBody& body = static_cast<IERigidBody&>(obj);

    in >> body.rigidbodyType >> body.attachedId >> body.density >> body.sleepThreshold;

    return in;
}
