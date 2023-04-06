#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState() :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(nullptr),
    input(nullptr),
    gRenderEngine(nullptr),
    eRenderEngine(nullptr),
    eCamera(std::make_unique<ECamera>())
{

}

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
    glFunc = nullptr;
    glExtraFunc = nullptr;
}

void IEGameStopState::enter(IEGame& game)
{
    game.makeCurrent();
    IESerialize::read<IEGame>("./resources/temp/game/game.iedat", &game);
    IESerialize::read<ECamera>("./resources/temp/editor/camera.iecam", &(*eCamera));

    eRenderEngine = std::make_unique<ERenderEngine>();

    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();

    time = &game.getIETime();
    input = &game.getIEInput();
    gRenderEngine = &game.getIERenderEngine();

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame& game)
{
    IESerialize::write<IEGame>("./resources/temp/game/game.iedat", &game);
    IESerialize::write<ECamera>("./resources/temp/editor/camera.iecam", &(*eCamera));
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
