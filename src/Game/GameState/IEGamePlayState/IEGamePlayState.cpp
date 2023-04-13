#include "IEGamePlayState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSScriptSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "ECSOnUpdateEvent.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(game.getTime()),
    physicsEngine(game.getPhysicsEngine()),
    gRenderEngine(game.getRenderEngine()),
    scriptSystem(game.getECS().getComponent<IEECSScriptSystem>("Script")),
    rigidbody3dSystem(game.getECS().getComponent<IEECSRigidbody3DSystem>("Rigidbody3D")),
    transformSystem(game.getECS().getComponent<IEECSTransformSystem>("Transform")),
    cameraSystem(game.getECS().getComponent<IEECSCameraSystem>("Camera")),
    ecsUpdateEvent(QSharedPointer<ECSOnUpdateEvent>::create(&game.getECS()))
{

}

IEGamePlayState::~IEGamePlayState()
{

}

void IEGamePlayState::enter(IEGame&)
{
    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGamePlayState::exit(IEGame&)
{

}

void IEGamePlayState::onUpdateFrame()
{
    const float dt = time.getDeltaTime();

    physicsEngine.onUpdateFrame(dt);
    scriptSystem->onUpdateFrame(&(*ecsUpdateEvent));
    rigidbody3dSystem->onUpdateFrame(&(*ecsUpdateEvent));
    transformSystem->onUpdateFrame(&(*ecsUpdateEvent));
    cameraSystem->onUpdateFrame(&(*ecsUpdateEvent));
}

void IEGamePlayState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto camera = cameraSystem->getActiveCamera();
    gRenderEngine.onRenderFrame(glExtraFunc, camera);
}

void IEGamePlayState::onResize(const float w, const float h)
{
    const int index = cameraSystem->getActiveIndex();
    auto camera = cameraSystem->getActiveCamera();
    auto script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    script->updateProjection(camera, w, h);
}













