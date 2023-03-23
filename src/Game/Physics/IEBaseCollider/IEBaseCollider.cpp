#include "IEBaseCollider.h"

IEBaseCollider::IEBaseCollider() :
    shape(nullptr), rigidActor(nullptr)
{

}

IEBaseCollider::~IEBaseCollider()
{

}

void IEBaseCollider::setIsTrigger(const bool val)
{
    shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !val);
    shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, val);
}
