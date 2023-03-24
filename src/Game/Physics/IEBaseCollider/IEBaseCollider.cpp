#include "IEBaseCollider.h"

IEBaseCollider::IEBaseCollider() :
    rigidActor(nullptr)
{

}

IEBaseCollider::~IEBaseCollider()
{

}

void IEBaseCollider::setIsTrigger(const bool val)
{
    physx::PxShape* shape;
    rigidActor->getShapes(&shape, 1);

    shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !val);
    shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, val);
}
