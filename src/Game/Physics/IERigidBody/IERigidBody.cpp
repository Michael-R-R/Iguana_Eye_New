#include "IERigidBody.h"
#include "IEPhysicsEngine.h"
#include "physx/extensions/PxSimpleFactory.h"

IERigidBody::IERigidBody() :
    rigidActor(nullptr),
    bodyType(BodyType::None)
{

}

IERigidBody::IERigidBody(physx::PxPhysics& p,
                         physx::PxMaterial& m,
                         const physx::PxTransform& t,
                         const physx::PxGeometry& g,
                         const int attachedId)
{
    this->createAsStatic(p, m, t, g);
    rigidActor->userData = (void*)(size_t)attachedId;
}

IERigidBody::IERigidBody(physx::PxPhysics& p,
                         physx::PxMaterial& m,
                         const physx::PxTransform& t,
                         const physx::PxGeometry& g,
                         const float density,
                         const float sleepThresh,
                         const int attachedId,
                         bool isKinematic)
{
    if(isKinematic)
        this->createAsKinematic(p, m, t, g, density, sleepThresh);
    else
        this->createAsDynamic(p, m, t, g, density, sleepThresh);

    rigidActor->userData = (void*)(size_t)attachedId;
}

IERigidBody::IERigidBody(const IERigidBody& other) :
    rigidActor(other.rigidActor),
    bodyType(other.bodyType)
{

}

IERigidBody::~IERigidBody()
{
    rigidActor = nullptr; // Manually clean up or let scene clean up
}

bool IERigidBody::wakeup(IEPhysicsEngine* engine)
{
    if(!rigidActor)
        return false;

    if(is(BodyType::None) || is(BodyType::Static))
        return false;

    engine->addActorToScene(rigidActor);

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->wakeUp();

    return true;
}

bool IERigidBody::putToSleep(IEPhysicsEngine* engine)
{
    if(!rigidActor)
        return false;

    if(is(BodyType::None) || is(BodyType::Static))
        return false;

    auto* temp = static_cast<physx::PxRigidDynamic*>(rigidActor);
    temp->putToSleep();

    engine->removeActorFromScene(rigidActor);

    return true;
}

void IERigidBody::release(IEPhysicsEngine* engine)
{
    engine->releaseActor(rigidActor);

    rigidActor = nullptr;
    bodyType = BodyType::None;
}

void IERigidBody::createAsStatic(physx::PxPhysics& physics,
                                 physx::PxMaterial& material,
                                 const physx::PxTransform& t,
                                 const physx::PxGeometry& geometry)
{
    auto* actor = physx::PxCreateStatic(physics, t, geometry, material);

    rigidActor = actor;
    bodyType = BodyType::Static;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, false);
}

void IERigidBody::createAsDynamic(physx::PxPhysics& physics,
                                  physx::PxMaterial& material,
                                  const physx::PxTransform& t,
                                  const physx::PxGeometry& geometry,
                                  const float density,
                                  const float sleepThresh)
{
    auto* actor = physx::PxCreateDynamic(physics, t, geometry, material, density);
    actor->setSleepThreshold(sleepThresh);

    rigidActor = actor;
    bodyType = BodyType::Dynamic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}

void IERigidBody::createAsKinematic(physx::PxPhysics& physics,
                                    physx::PxMaterial& material,
                                    const physx::PxTransform& t,
                                    const physx::PxGeometry& geometry,
                                    const float density,
                                    const float sleepThresh)
{
    auto* actor = physx::PxCreateKinematic(physics, t, geometry, material, density);
    actor->setSleepThreshold(sleepThresh);

    rigidActor = actor;
    bodyType = BodyType::Kinematic;

    rigidActor->setActorFlag(physx::PxActorFlag::eSEND_SLEEP_NOTIFIES, true);
}
