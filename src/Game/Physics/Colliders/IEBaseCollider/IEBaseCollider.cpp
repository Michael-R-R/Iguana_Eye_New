#include "IEBaseCollider.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "physx/extensions/PxSimpleFactory.h"

IEBaseCollider::IEBaseCollider(QObject* parent) :
    IEObject(parent),
    rigidActor(nullptr),
    colliderShape(ColliderShape::None), attachedId(0)
{

}

IEBaseCollider::IEBaseCollider(ColliderShape shape,
                               const int id,
                               QObject* parent) :
    IEObject(parent),
    rigidActor(nullptr),
    colliderShape(shape), attachedId(id)
{

}

IEBaseCollider::~IEBaseCollider()
{

}

void IEBaseCollider::release()
{
    if(!rigidActor)
        return;

    rigidActor->release();
}

void IEBaseCollider::setIsTrigger(const bool val)
{
    if(!rigidActor)
        return;

    physx::PxShape* shape;
    rigidActor->getShapes(&shape, 1);

    shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !val);
    shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, val);
}

physx::PxVec3 IEBaseCollider::getGlobalPos() const
{
    if(!rigidActor)
        return physx::PxVec3();

    return rigidActor->getGlobalPose().p;
}

physx::PxQuat IEBaseCollider::getGlobalQuat() const
{
    if(!rigidActor)
        return physx::PxQuat();

    return rigidActor->getGlobalPose().q;
}

void IEBaseCollider::create(const physx::PxTransform& t, const physx::PxGeometry& g)
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* engine = game->getPhysicsEngine();

    auto& p = engine->getPxPhysics();
    auto& m = engine->getPxMaterial();

    auto* actor = physx::PxCreateStatic(p, t, g, m);

    rigidActor = actor;
    rigidActor->userData = (void*)(size_t)attachedId;
}

QDataStream& IEBaseCollider::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEBaseCollider& collider = static_cast<const IEBaseCollider&>(obj);

    out << collider.colliderShape << collider.attachedId;

    return out;
}

QDataStream& IEBaseCollider::deserialize(QDataStream& in, Serializable& obj)
{
    IEBaseCollider& collider = static_cast<IEBaseCollider&>(obj);

    in >> collider.colliderShape >> collider.attachedId;

    return in;
}
