#include "IEGamePlayState.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEECSScriptSystem.h"
#include "IEECSRigidbody3DSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "ECSOnUpdateEvent.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(game.getIETime()),
    physicsEngine(game.getIEPhysicsEngine()),
    renderEngine(game.getIERenderEngine()),
    scriptSystem(nullptr),
    rigidbody3dSystem(nullptr),
    transformSystem(nullptr),
    cameraSystem(nullptr),
    ecsUpdateEvent(nullptr)
{

}

IEGamePlayState::~IEGamePlayState()
{

}

void IEGamePlayState::enter(IEGame& game)
{
    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();

    auto& ecs = game.getIEScene().getECS();
    scriptSystem = ecs.getComponent<IEECSScriptSystem>("Script");
    rigidbody3dSystem = ecs.getComponent<IEECSRigidbody3DSystem>("Rigidbody3D");
    transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
    cameraSystem = ecs.getComponent<IEECSCameraSystem>("Camera");
    ecsUpdateEvent = std::make_unique<ECSOnUpdateEvent>(&ecs);

    // Serialize everything to temp file

    // Set game camera as active
}

void IEGamePlayState::exit(IEGame&)
{
    // Deserialize everything back from temp file

    // Set editor camera as active
}

void IEGamePlayState::onUpdateFrame()
{
    physicsEngine.onUpdateFrame(time.getDeltaTime());
    scriptSystem->onUpdateFrame(&(*ecsUpdateEvent));
    rigidbody3dSystem->onUpdateFrame(&(*ecsUpdateEvent));
    transformSystem->onUpdateFrame(&(*ecsUpdateEvent));
    cameraSystem->onUpdateFrame(&(*ecsUpdateEvent));
}

void IEGamePlayState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderEngine.onRenderFrame(cameraSystem->getActiveCamera());
    time.processDeltaTime();
}
