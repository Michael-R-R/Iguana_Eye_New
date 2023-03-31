#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "ECamera.h"

IEGameStopState::IEGameStopState() :
    glFunc(nullptr),
    glExtraFunc(nullptr),
    time(nullptr),
    input(nullptr),
    renderEngine(nullptr),
    camera(std::make_unique<ECamera>())
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

    time = &game.getIETime();
    input = &game.getIEInput();
    renderEngine = &game.getIERenderEngine();

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame&)
{

}

void IEGameStopState::onUpdateFrame()
{
    camera->update(*input, time->getDeltaTime());
}

void IEGameStopState::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderEngine->onRenderFrame(&(*camera));
    time->processDeltaTime();
}

void IEGameStopState::onResize(const float w, const float h)
{
    camera->updateProjection(w, h);
}
