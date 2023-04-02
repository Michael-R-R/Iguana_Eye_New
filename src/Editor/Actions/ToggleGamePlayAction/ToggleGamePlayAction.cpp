#include "ToggleGamePlayAction.h"
#include "IEGamePlayState.h"
#include "IEGame.h"

ToggleGamePlayAction::ToggleGamePlayAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Play", shortcut, parent)
{
    connect(this, &ToggleGamePlayAction::triggered, this, [&game]()
    {
        auto playState = std::make_unique<IEGamePlayState>();
        game.setState(std::move(playState));
    });
}

ToggleGamePlayAction::~ToggleGamePlayAction()
{

}
