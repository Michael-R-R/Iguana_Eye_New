#include "ToggleGamePlayAction.h"
#include "IEGame.h"

ToggleGamePlayAction::ToggleGamePlayAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Play", shortcut, parent)
{
    connect(this, &ToggleGamePlayAction::triggered, this, [&game]()
    {
        game.play();
    });
}

ToggleGamePlayAction::~ToggleGamePlayAction()
{

}
