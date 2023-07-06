#include "IEPhysicsEngine.h"

IEPhysicsEngine::IEPhysicsEngine(QObject* parent) :
    IESystem(parent),
    defaultAllocatorCallback(),
    defaultErrorCallback(),
    pxCpuDispatcher(nullptr),
    pxToleranceScale(),
    pxFoundation(nullptr),
    pxPhysics(nullptr),
    pxScene(nullptr),
    pxMaterial(nullptr),
    simulationCallback(),
    worldGravity(-9.81f),
    accumulator(0.0f),
    stepSize(1.0f / 60.0f)
{

}

IEPhysicsEngine::~IEPhysicsEngine()
{

}

void IEPhysicsEngine::startup(IEGame&)
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
    if(!pxFoundation)
        throw("PxCreateFoundation failed");

    pxToleranceScale.length = 100;
    pxToleranceScale.speed = 981;
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, pxToleranceScale, true);

    pxCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);

    pxScene = pxPhysics->createScene(createSceneDesc());
    pxMaterial = pxPhysics->createMaterial(1.0f, 1.0f, 0.5f);
}

void IEPhysicsEngine::shutdown(IEGame&)
{
    pxScene->release();
    pxCpuDispatcher->release();
    pxPhysics->release();
    pxFoundation->release();
}

void IEPhysicsEngine::onDeserialize(IEGame&)
{
    pxScene->release();
    pxScene = pxPhysics->createScene(createSceneDesc());
}

void IEPhysicsEngine::onUpdateFrame(const float dt)
{
    accumulator += dt;
    if(accumulator < stepSize)
        return;

    accumulator -= stepSize;

    pxScene->simulate(stepSize);
    pxScene->fetchResults(true);
}

void IEPhysicsEngine::addActorToScene(physx::PxActor* actor)
{
    if(!actor)
        return;

    pxScene->addActor(*actor);
}

void IEPhysicsEngine::removeActorFromScene(physx::PxActor* actor)
{
    if(!actor)
        return;

    pxScene->removeActor(*actor);
}

void IEPhysicsEngine::releaseActor(physx::PxActor* actor)
{
    if(!actor)
        return;

    pxScene->removeActor(*actor);
    actor->release();
}

physx::PxSceneDesc IEPhysicsEngine::createSceneDesc()
{
    physx::PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, worldGravity, 0.0f);
    sceneDesc.cpuDispatcher = pxCpuDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    sceneDesc.simulationEventCallback = &simulationCallback;

    return sceneDesc;
}
