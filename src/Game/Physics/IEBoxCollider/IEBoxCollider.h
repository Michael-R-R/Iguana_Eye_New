#pragma once

#include "IEBaseCollider.h"

class IEBoxCollider : public IEBaseCollider
{

public:
    IEBoxCollider(physx::PxPhysics& physics,
                  physx::PxMaterial& material,
                  const physx::PxBoxGeometry& box,
                  const physx::PxTransform& t,
                  const int attachedId);
    ~IEBoxCollider();

protected:
    void createShape(physx::PxPhysics& physics,
                     physx::PxMaterial& material,
                     const physx::PxGeometry& box,
                     const physx::PxTransform& t) override;
};

