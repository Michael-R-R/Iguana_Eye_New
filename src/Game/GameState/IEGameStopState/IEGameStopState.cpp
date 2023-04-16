#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "IEScriptEngine.h"
#include "IEECS.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"
#include "EPhysicsEngine.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IEFile.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(game.getTime()),
    input(game.getInput()),
    gRenderEngine(game.getRenderEngine()),
    transformSystem(game.getECS().getComponent<IEECSTransformSystem>()),
    ecsUpdateEvent(QSharedPointer<ECSOnUpdateEvent>::create(&game.getECS())),
    ePhysicsEngine(nullptr),
    eRenderEngine(nullptr),
    eCamera(nullptr)
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame& game)
{
    ePhysicsEngine = QSharedPointer<EPhysicsEngine>::create();
    eRenderEngine = QSharedPointer<ERenderEngine>::create();
    eCamera = QSharedPointer<ECamera>::create();

    deserializeGameStates(game);

    ePhysicsEngine->startup(game);

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame& game)
{
    serializeGameStates(game);

    ePhysicsEngine->shutdown();
}

void IEGameStopState::onUpdateFrame()
{
    const float dt = time.getDeltaTime();

    eCamera->update(input, dt);
    transformSystem->onUpdateFrame(&(*ecsUpdateEvent));
    ePhysicsEngine->onUpdateFrame(input, *eCamera);
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gRenderEngine.onRenderFrame(glExtraFunc, eCamera);
    eRenderEngine->onRenderFrame(glExtraFunc, eCamera);
}

void IEGameStopState::onResize(const float w, const float h)
{
    eCamera->updateProjection(w, h);
}

void IEGameStopState::serializeGameStates(IEGame& game)
{
    IESerialize::write<IEECS>("./resources/temp/backup/ecs.iedat", &game.getECS());
    IESerialize::write<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));
}

void IEGameStopState::deserializeGameStates(IEGame& game)
{
    IESerialize::read<IEECS>("./resources/temp/backup/ecs.iedat", &game.getECS());
    IESerialize::read<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));

    IEFile::removeAllFiles("./resources/temp/backup/");
}
