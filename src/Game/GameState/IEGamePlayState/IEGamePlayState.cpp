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

IEGamePlayState::IEGamePlayState() :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(nullptr),
    input(nullptr),
    physicsEngine(nullptr),
    renderEngine(nullptr),
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

    time = &game.getIETime();
    input = &game.getIEInput();
    physicsEngine = &game.getIEPhysicsEngine();
    renderEngine = &game.getIERenderEngine();

    auto& ecs = game.getECS();
    scriptSystem = ecs.getComponent<IEECSScriptSystem>("Script");
    rigidbody3dSystem = ecs.getComponent<IEECSRigidbody3DSystem>("Rigidbody3D");
    transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
    cameraSystem = ecs.getComponent<IEECSCameraSystem>("Camera");
    ecsUpdateEvent = std::make_unique<ECSOnUpdateEvent>(&ecs);

    // TODO test
    auto* rigidbodySystem = ecs.getComponent<IEECSRigidbody3DSystem>("Rigidbody3D");
    rigidbodySystem->play();

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGamePlayState::exit(IEGame&)
{

}

void IEGamePlayState::onUpdateFrame()
{
    physicsEngine->onUpdateFrame(time->getDeltaTime());
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
    IECameraScript* script = cameraSystem->getScript(index);
    if(!camera || !script)
        return;

    script->updateProjection(camera, w, h);
}













