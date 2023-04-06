#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEECS.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(&game.getIETime()),
    input(&game.getIEInput()),
    gRenderEngine(&game.getIERenderEngine()),
    eRenderEngine(std::make_unique<ERenderEngine>()),
    eCamera(std::make_unique<ECamera>())
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame& game)
{
    deserializeGameStates(game);

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame& game)
{
    serializeGameStates(game);
}

void IEGameStopState::onUpdateFrame()
{
    eCamera->update(*input, time->getDeltaTime());
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gRenderEngine->onRenderFrame(&(*eCamera));
    eRenderEngine->onRenderFrame(glExtraFunc, &(*eCamera));
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
}
