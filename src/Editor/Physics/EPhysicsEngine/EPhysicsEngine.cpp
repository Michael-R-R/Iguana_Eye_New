#include "EPhysicsEngine.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"

EPhysicsEngine::EPhysicsEngine(IEGame& game) :
    pxScene(nullptr), pxMaterial(nullptr),
    rigidbodies()
{
    setup(game);
}

EPhysicsEngine::~EPhysicsEngine()
{
    pxMaterial->release();
    pxScene->release();
}

void EPhysicsEngine::onUpdateFrame()
{

}

void EPhysicsEngine::setup(IEGame& game)
{
    auto& engine = game.getPhysicsEngine();
    auto& p = engine.getPxPhysics();
    auto& cpuDispatcher = engine.getCpuDispatcher();

    physx::PxSceneDesc sceneDesc(p.getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);
    sceneDesc.cpuDispatcher = &cpuDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

    pxScene = p.createScene(sceneDesc);
    pxMaterial = p.createMaterial(0.0f, 0.0f, 0.0f);
}

