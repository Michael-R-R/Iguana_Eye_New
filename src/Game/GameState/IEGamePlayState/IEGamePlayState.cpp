#include "IEGamePlayState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IETime.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSCameraSystem.h"
#include "IECamera.h"

IEGamePlayState::IEGamePlayState(QObject* parent) :
    IEGameState(parent),
    time(nullptr),
    pEngine(nullptr),
    rEngine(nullptr),
    ecs(nullptr),
    cameraSystem(nullptr)
{

}

IEGamePlayState::~IEGamePlayState()
{

}

void IEGamePlayState::enter(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();

    time = game.getSystem<IETime>();
    pEngine = scene->getSystem<IEPhysicsEngine>();
    rEngine = scene->getSystem<IERenderEngine>();
    ecs = scene->getSystem<IEECS>();

    cameraSystem = ecs->getComponent<IEECSCameraSystem>();

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGamePlayState::exit(IEGame&)
{

}

void IEGamePlayState::onUpdateFrame()
{
    const float dt = time->getDeltaTime();

    pEngine->onUpdateFrame(dt);
    ecs->onUpdateFrame();
}

void IEGamePlayState::onRenderFrame()
{
    auto* camera = cameraSystem->getActiveCamera();

    rEngine->onRenderFrame(camera);
    time->processDeltaTime();
}

void IEGamePlayState::onResize(const float w, const float h)
{
    const int index = cameraSystem->getActiveIndex();
    auto* camera = cameraSystem->getActiveCamera();
    auto* script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    auto func = script->getCustomFunc("updateProjection");
    func(camera, w, h);
}













