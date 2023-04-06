#include "ToggleGameStopAction.h"
#include "IEGame.h"

ToggleGameStopAction::ToggleGameStopAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Stop", shortcut, parent)
{
    connect(this, &ToggleGameStopAction::triggered, this, [&game]()
    {
        game.stop();
    });
}

ToggleGameStopAction::~ToggleGameStopAction()
{

}
