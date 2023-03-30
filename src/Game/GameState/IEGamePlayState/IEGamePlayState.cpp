#include "IEGamePlayState.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEScene.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"

IEGamePlayState::IEGamePlayState(IEGame& game) :
    time(game.getIETime()),
    physicsEngine(game.getIEPhysicsEngine()),
    renderEngine(game.getIERenderEngine()),
    scene(game.getIEScene()),
    glFunc(nullptr),
    glExtraFunc(nullptr)
{

}

IEGamePlayState::~IEGamePlayState()
{

}

void IEGamePlayState::enter(IEGame& game)
{
    // Serialize everything to temp file

    // Set game camera as active

    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();
}

void IEGamePlayState::exit(IEGame&)
{
    // Deserialize everything back from temp file

    // Set editor camera as active
}

void IEGamePlayState::onUpdateFrame(IEGame&)
{
    physicsEngine.onUpdateFrame(time.getDeltaTime());
    scene.onUpdateFrame();
}

void IEGamePlayState::onRenderFrame(IEGame&)
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderEngine.onRenderFrame();
    time.processDeltaTime();
}
