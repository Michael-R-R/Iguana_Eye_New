#include "IEGamePlayState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSCameraSystem.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(game.getTime()),
    physicsEngine(game.getPhysicsEngine()),
    renderEngine(game.getRenderEngine()),
    ecs(game.getECS()),
    ecsUpdateEvent(*ecs)
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
    const float dt = time->getDeltaTime();

    physicsEngine->onUpdateFrame(dt);
    ecs->onUpdateFrame(ecsUpdateEvent);
}

void IEGamePlayState::onRenderFrame()
{
    auto& cameraSystem = ecsUpdateEvent.getCamera();
    auto* camera = cameraSystem.getActiveCamera();

    renderEngine->onRenderFrame(glExtraFunc, camera);
}

void IEGamePlayState::onResize(const float w, const float h)
{
    auto& cameraSystem = ecsUpdateEvent.getCamera();

    const int index = cameraSystem.getActiveIndex();
    auto camera = cameraSystem.getActiveCamera();
    auto script = cameraSystem.getScript(index);
    if(!camera || !script)
        return;

    script->updateProjection(camera, w, h);
}













