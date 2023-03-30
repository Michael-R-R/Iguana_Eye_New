#include "IEGameStopState.h"
#include "IETime.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IERenderEngine.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "ECSOnUpdateEvent.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(game.getIETime()),
    renderEngine(game.getIERenderEngine()),
    transformSystem(nullptr),
    cameraSystem(nullptr),
    ecsUpdateEvent(nullptr)
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame& game)
{
    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();

    auto& ecs = game.getIEScene().getECS();
    transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
    cameraSystem = ecs.getComponent<IEECSCameraSystem>("Camera");
    ecsUpdateEvent = std::make_unique<ECSOnUpdateEvent>(&ecs);
}

void IEGameStopState::exit(IEGame&)
{

}

void IEGameStopState::onUpdateFrame()
{
    transformSystem->onUpdateFrame(&(*ecsUpdateEvent));
    cameraSystem->onUpdateFrame(&(*ecsUpdateEvent));
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderEngine.onRenderFrame();
    time.processDeltaTime();
}
