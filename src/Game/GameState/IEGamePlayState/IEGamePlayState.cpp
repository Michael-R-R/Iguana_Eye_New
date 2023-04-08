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
    scriptSystem(IEECS::instance().getComponent<IEECSScriptSystem>("Script")),
    rigidbody3dSystem(IEECS::instance().getComponent<IEECSRigidbody3DSystem>("Rigidbody3D")),
    transformSystem(IEECS::instance().getComponent<IEECSTransformSystem>("Transform")),
    cameraSystem(IEECS::instance().getComponent<IEECSCameraSystem>("Camera")),
    ecsUpdateEvent(std::make_unique<ECSOnUpdateEvent>(&IEECS::instance()))
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
    const float dt = IETime::instance().getDeltaTime();

    IEPhysicsEngine::instance().onUpdateFrame(dt);
    scriptSystem->onUpdateFrame(&(*ecsUpdateEvent));
    rigidbody3dSystem->onUpdateFrame(&(*ecsUpdateEvent));
    transformSystem->onUpdateFrame(&(*ecsUpdateEvent));
    cameraSystem->onUpdateFrame(&(*ecsUpdateEvent));
}

void IEGamePlayState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto* camera = cameraSystem->getActiveCamera();
    IERenderEngine::instance().onRenderFrame(camera);
}

void IEGamePlayState::onResize(const float w, const float h)
{
    const int index = cameraSystem->getActiveIndex();
    IECamera* camera = cameraSystem->getActiveCamera();
    const QSharedPointer<IECameraScript> script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    script->updateProjection(camera, w, h);
}













