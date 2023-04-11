#pragma once

#include "IEBaseCollider.h"

class IEBoxCollider : public IEBaseCollider
{

    float extentX, extentY, extentZ;

public:
    IEBoxCollider(physx::PxPhysics* p,
                  physx::PxMaterial* m);
    IEBoxCollider(physx::PxPhysics* p,
                  physx::PxMaterial* m,
                  const int id,
                  const float x, const float y, const float z);
    IEBoxCollider(const IEBoxCollider&) = delete;
    ~IEBoxCollider();

    void create(const physx::PxTransform& t) override;
};

