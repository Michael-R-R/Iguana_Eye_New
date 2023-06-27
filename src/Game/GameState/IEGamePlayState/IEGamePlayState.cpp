#include "IEGamePlayState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSCameraSystem.h"
#include "IECamera.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(game.getTime()),
    physicsEngine(game.getPhysicsEngine()),
    renderEngine(game.getRenderEngine()),
    ecs(game.getECS())
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
    ecs->onUpdateFrame();
}

void IEGamePlayState::onRenderFrame()
{
    auto* cameraSystem = ecs->getComponent<IEECSCameraSystem>();
    auto* camera = cameraSystem->getActiveCamera();

    renderEngine->onRenderFrame(glExtraFunc, camera);
}

void IEGamePlayState::onResize(const float w, const float h)
{
    auto* cameraSystem = ecs->getComponent<IEECSCameraSystem>();

    const int index = cameraSystem->getActiveIndex();
    auto* camera = cameraSystem->getActiveCamera();
    auto* script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    auto func = script->getCustomFunc("updateProjection");
    func(camera, w, h);
}













