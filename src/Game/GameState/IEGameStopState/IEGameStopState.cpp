#include "IEGameStopState.h"
#include "IETime.h"
#include "IEGame.h"
#include "IERenderEngine.h"
#include "EDefaultCamera.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(game.getIETime()),
    renderEngine(game.getIERenderEngine()),
    camera(std::make_unique<EDefaultCamera>())
{

}

IEGameStopState::~IEGameStopState()
{
    glFunc = nullptr;
    glExtraFunc = nullptr;
}

void IEGameStopState::enter(IEGame& game)
{
    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();
}

void IEGameStopState::exit(IEGame&)
{

}

void IEGameStopState::onUpdateFrame()
{
    // TODO update the custom camera for stop state
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderEngine.onRenderFrame(&(*camera)); // TODO need to pass a editor camera
    time.processDeltaTime();
}
