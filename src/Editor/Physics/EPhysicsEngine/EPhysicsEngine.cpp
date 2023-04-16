#include "EPhysicsEngine.h"
#include "IEGame.h"
#include "IEInput.h"
#include "ECamera.h"
#include "IEPhysicsEngine.h"
#include "IEBoxRigidBody.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "IEMath.h"
#include "ApplicationProperties.h"

EPhysicsEngine::EPhysicsEngine() :
    pxScene(nullptr),
    raycastDistance(10000.0f),
    filterFlag(physx::PxQueryFlag::eSTATIC),
    rigidbodies()
{

}

EPhysicsEngine::~EPhysicsEngine()
{

}

void EPhysicsEngine::startup(IEGame& game)
{
    auto& engine = game.getPhysicsEngine();
    auto& p = engine.getPxPhysics();
    auto& cpuDispatcher = engine.getCpuDispatcher();

    physx::PxSceneDesc sceneDesc(p.getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, 0.0f, 0.0f);
    sceneDesc.cpuDispatcher = &cpuDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

    pxScene = p.createScene(sceneDesc);

    onInitRigidbodies(game);
}

void EPhysicsEngine::shutdown()
{
    pxScene->release();
}

void EPhysicsEngine::onUpdateFrame(IEInput& input, ECamera& camera)
{
    if(input.isPressed("Left Click"))
    {
        castRay(input, camera);
    }
}

void EPhysicsEngine::onInitRigidbodies(IEGame& game)
{
    auto& ecs = game.getECS();
    auto* system = ecs.getComponent<IEECSTransformSystem>();
    const auto& data = system->getData();

    auto type = IEBaseRigidbody::RigidbodyType::Static;

    for(int i = 1; i < data.entity.size(); i++)
    {
        const IEEntity entity = data.entity[i];
        const int id = entity.getId();
        const auto& pos = data.position[i];
        const auto& rot = data.rotation[i];
        const auto& scl = data.scale[i];

        auto box = QSharedPointer<IEBoxRigidbody>::create(type, id, scl.x(), scl.y(), scl.z());

        physx::PxTransform pt(pos.x(), pos.y(), pos.z());
        physx::PxTransform pq(physx::PxQuat(rot.x(), rot.y(), rot.z(), rot.w()));
        physx::PxTransform t = pt * pq;
        box->create(pt);

        rigidbodies[entity] = box;

        pxScene->addActor(*box->getActor());
    }
}

void EPhysicsEngine::castRay(IEInput& input, ECamera& camera)
{
    const QVector3D& pos = camera.getPosition();
    const QVector2D& dimensions = ApplicationProperties::viewportDimensions;
    const QVector3D worldRay = IEMath::toWorldRay(dimensions.x(), dimensions.y(),
                                                  input.cursorPos(),
                                                  camera.getView(),
                                                  camera.getProjection());

    physx::PxVec3 origin(pos.x(), pos.y(), pos.z());
    physx::PxVec3 dir(worldRay.x(), worldRay.y(), worldRay.z());
    physx::PxRaycastBuffer hit;

    bool status = pxScene->raycast(origin, dir, raycastDistance, hit, physx::PxHitFlag::eDEFAULT, filterFlag);
    if(status)
    {
        auto* actor = hit.block.actor;
        if(actor)
            qDebug() << "Hit: " << (int)(size_t)actor->userData;
    }
    else
        qDebug() << "No hit";
}
