#include "IEPhysicsEngine.h"

IEPhysicsEngine::IEPhysicsEngine() :
    defaultAllocatorCallback(),
    defaultErrorCallback(),
    pxCpuDispatcher(nullptr),
    pxToleranceScale(),
    pxFoundation(nullptr),
    pxPhysics(nullptr),
    pxScene(nullptr),
    pxDefaultMaterial(nullptr),
    simulationCallback(nullptr),
    worldGravity(-9.81f),
    accumulator(0.0f),
    stepSize(1.0f / 60.0f)
{

}

IEPhysicsEngine::~IEPhysicsEngine()
{

}

void IEPhysicsEngine::startup(const GameStartEvent&)
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
    if(!pxFoundation)
        throw("PxCreateFoundation failed");

    pxToleranceScale.length = 100;
    pxToleranceScale.speed = 981;
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, pxToleranceScale, true);

    pxCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    simulationCallback = std::make_unique<IESimulationCallback>(this);

    physx::PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, worldGravity, 0.0f);
    sceneDesc.cpuDispatcher = pxCpuDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    sceneDesc.simulationEventCallback = &(*simulationCallback);

    pxScene = pxPhysics->createScene(sceneDesc);
    pxDefaultMaterial = pxPhysics->createMaterial(1.0f, 1.0f, 0.5f);

    emit message("Physics Engine Started");
}

void IEPhysicsEngine::shutdown()
{
    pxScene->release();
    pxCpuDispatcher->release();
    pxPhysics->release();
    pxFoundation->release();

    emit message("Physics Engine Shutdowned");
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

















