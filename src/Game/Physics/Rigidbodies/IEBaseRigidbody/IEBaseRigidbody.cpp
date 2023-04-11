#include "IEBaseRigidbody.h"
#include "IEPhysicsEngine.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBaseRigidbody::IEBaseRigidbody() :
    rigidActor(nullptr),
    rigidbodyType(RigidbodyType::None),
    rigidbodyShape(RigidbodyShape::None),
    attachedId(0), density(1.0f), sleepThreshold(1.0f)
{

}

IEBaseRigidbody::IEBaseRigidbody(RigidbodyType type,
                                 RigidbodyShape shape,
                                 const int id,
                                 const float d,
                                 const float st) :
    rigidActor(nullptr),
    rigidbodyType(type), rigidbodyShape(shape),
    attachedId(id), density(d), sleepThreshold(st)
{

}

IEBaseRigidbody::~IEBaseRigidbody()
{
    if(rigidActor)
        rigidActor->release();
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
    rigidActor = nullptr;
    rigidbodyType = RigidbodyType::None;
    rigidbodyShape = RigidbodyShape::None;
}

physx::PxVec3 IEBaseRigidbody::getGlobalPos() const
{
    if(!rigidActor)
        return physx::PxVec3();

    return rigidActor->getGlobalPose().p;
}

physx::PxQuat IEBaseRigidbody::getGlobalQuat() const
{
    if(!rigidActor)
        return physx::PxQuat();

    return rigidActor->getGlobalPose().q;
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
    auto* p = IEPhysicsEngine::instance().getPxPhysics();
    auto* m = IEPhysicsEngine::instance().getPxMaterial();

    auto* actor = physx::PxCreateStatic(*p, t, geometry, *m);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);

    IEPhysicsEngine::instance().addActorToScene(rigidActor);
}

void IEBaseRigidbody::createAsDynamic(const physx::PxTransform& t,
                                      const physx::PxGeometry& geometry)
{
    auto* p = IEPhysicsEngine::instance().getPxPhysics();
    auto* m = IEPhysicsEngine::instance().getPxMaterial();

    auto* actor = physx::PxCreateDynamic(*p, t, geometry, *m, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);

    IEPhysicsEngine::instance().addActorToScene(rigidActor);
}

void IEBaseRigidbody::createAsKinematic(const physx::PxTransform& t,
                                        const physx::PxGeometry& geometry)
{
    auto* p = IEPhysicsEngine::instance().getPxPhysics();
    auto* m = IEPhysicsEngine::instance().getPxMaterial();

    auto* actor = physx::PxCreateKinematic(*p, t, geometry, *m, density);
    actor->setSleepThreshold(sleepThreshold);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
    rigidbodyType = RigidbodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);

    IEPhysicsEngine::instance().addActorToScene(rigidActor);
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
