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
                game->onDeserialize();
                game->changeState(new IEGameStopState(game));

                this->setEnabled(false);
            });

    connect(game, &IEGame::stateChanged, this, [this](const IEGameState* state)
            {
                if(dynamic_cast<const IEGamePlayState*>(state))
                    this->setEnabled(true);
            });
}

ToggleGameStopAction::~ToggleGameStopAction()
{

}
