#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "IEScriptEngine.h"
#include "IEECS.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IEFile.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    eRenderEngine(nullptr),
    eCamera(nullptr)
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame&)
{
    eRenderEngine = std::make_unique<ERenderEngine>();
    eCamera = std::make_unique<ECamera>();

    deserializeGameStates();

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame&)
{
    serializeGameStates();
}

void IEGameStopState::onUpdateFrame()
{
    const float dt = IETime::instance().getDeltaTime();

    eCamera->update(IEInput::instance(), dt);
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    IERenderEngine::instance().onRenderFrame(&(*eCamera));
    eRenderEngine->onRenderFrame(glExtraFunc, &(*eCamera));
}

void IEGameStopState::onResize(const float w, const float h)
{
    eCamera->updateProjection(w, h);
}

void IEGameStopState::serializeGameStates()
{
    IESerialize::write<IEECS>("./resources/temp/backup/ecs.iedat", &IEECS::instance());
    IESerialize::write<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));
}

void IEGameStopState::deserializeGameStates()
{
    IESerialize::read<IEECS>("./resources/temp/backup/ecs.iedat", &IEECS::instance());
    IESerialize::read<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));

    IEFile::removeAllFiles("./resources/temp/backup/");
}
