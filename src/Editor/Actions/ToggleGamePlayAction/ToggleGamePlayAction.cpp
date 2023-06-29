#include "ToggleGamePlayAction.h"
#include "IEGame.h"
#include "IEGamePlayState.h"
#include "IEGameStopState.h"

ToggleGamePlayAction::ToggleGamePlayAction(IEGame* game, InputKey& shortcut, QObject* parent) :
    BaseAction("Play", shortcut, parent)
{
    connect(this, &ToggleGamePlayAction::triggered, this, [this, game]()
            {
                game->changeState(new IEGamePlayState(game));

                this->setEnabled(false);
            });

    connect(game, &IEGame::stateChanged, this, [this](const IEGameState* state)
            {
                if(!static_cast<const IEGameStopState*>(state))
                    return;

                this->setEnabled(true);
            });
}

ToggleGamePlayAction::~ToggleGamePlayAction()
{

}
