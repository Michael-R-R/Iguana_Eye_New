#pragma once

#include "physx/PxPhysicsAPI.h"

#include "physx/extensions/PxDefaultAllocator.h"
#include "physx/extensions/PxDefaultErrorCallback.h"

class PhysicsTest
{
    physx::PxDefaultAllocator defaultAllocatorCallback;
    physx::PxDefaultErrorCallback defaultErrorCallback;


public:
    PhysicsTest();
    ~PhysicsTest();
};

