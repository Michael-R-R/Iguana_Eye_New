#pragma once

#include "IEBaseCollider.h"

class IEBoxCollider : public IEBaseCollider
{

public:
    IEBoxCollider(physx::PxPhysics& physics,
                  physx::PxMaterial& material,
                  const physx::PxGeometry& geometry,
                  const physx::PxTransform& t,
                  const int attachedId);
    ~IEBoxCollider();

protected:
    void createShape(physx::PxPhysics& physics,
                     physx::PxMaterial& material,
                     const physx::PxGeometry& geometry,
                     const physx::PxTransform& t) override;
};

