#include "ToggleGameStopAction.h"
#include "IEGameStopState.h"
#include "IEGame.h"

ToggleGameStopAction::ToggleGameStopAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Stop", shortcut, parent)
{
    connect(this, &ToggleGameStopAction::triggered, this, [&game]()
    {
        auto stopState = std::make_unique<IEGameStopState>();
        game.setState(std::move(stopState));
    });
}

ToggleGameStopAction::~ToggleGameStopAction()
{

}
