#include "ToggleGamePlayAction.h"
#include "IEGame.h"
#include "IEGamePlayState.h"

ToggleGamePlayAction::ToggleGamePlayAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Play", shortcut, parent)
{
    connect(this, &ToggleGamePlayAction::triggered, this, [&game]()
    {
        game.initalize();
        game.changeState(std::move(std::make_unique<IEGamePlayState>(game)));
    });
}

ToggleGamePlayAction::~ToggleGamePlayAction()
{

}
