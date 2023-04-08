#include "ToggleGameStopAction.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "IEScriptEngine.h"
#include "IEECS.h"
#include "IEGameStopState.h"

ToggleGameStopAction::ToggleGameStopAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Stop", shortcut, parent)
{
    connect(this, &ToggleGameStopAction::triggered, this, [&game]()
    {
        game.reset();
        game.changeState(QSharedPointer<IEGameStopState>::create(game));
    });
}

ToggleGameStopAction::~ToggleGameStopAction()
{

}
