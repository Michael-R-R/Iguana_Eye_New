#include "ToggleGameStopAction.h"
#include "IEGame.h"
#include "IEGameStopState.h"
#include "IEGamePlayState.h"

ToggleGameStopAction::ToggleGameStopAction(IEGame* game, InputKey& shortcut, QObject* parent) :
    BaseAction("Stop", shortcut, parent)
{
    this->setEnabled(false);

    connect(this, &ToggleGameStopAction::triggered, this, [this, game]()
            {
                game->changeState(new IEGameStopState(game));

                this->setEnabled(false);
            });

    connect(game, &IEGame::stateChanged, this, [this](const IEGameState* state)
            {
                if(!static_cast<const IEGamePlayState*>(state))
                    return;

                this->setEnabled(true);
            });
}

ToggleGameStopAction::~ToggleGameStopAction()
{

}
