#include "IEGamePlayState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSScriptSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "ECSOnUpdateEvent.h"
#include "IESerialize.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    renderEngine(&game.getIERenderEngine()),
    ecs(&game.getECS()),
    scriptSystem(ecs->getComponent<IEECSScriptSystem>("Script")),
    rigidbody3dSystem(ecs->getComponent<IEECSRigidbody3DSystem>("Rigidbody3D")),
    transformSystem(ecs->getComponent<IEECSTransformSystem>("Transform")),
    cameraSystem(ecs->getComponent<IEECSCameraSystem>("Camera")),
    ecsUpdateEvent(std::make_unique<ECSOnUpdateEvent>(ecs))
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
    renderEngine->onRenderFrame(cameraSystem->getActiveCamera());
}

void IEGamePlayState::onResize(const float w, const float h)
{
    const int index = cameraSystem->getActiveIndex();
    IECamera* camera = cameraSystem->getActiveCamera();
    const IECameraScript* script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    script->updateProjection(camera, w, h);
}













