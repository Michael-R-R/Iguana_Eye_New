#include "ToggleGamePlayAction.h"
#include "IEGame.h"
#include "IEGamePlayState.h"
#include "IEGameStopState.h"

ToggleGamePlayAction::ToggleGamePlayAction(IEGame& game, InputKey& shortcut, QObject* parent) :
    BaseAction("Play", shortcut, parent)
{
    connect(this, &ToggleGamePlayAction::triggered, this, [this, &game]()
    {
        game.initalize();
        game.changeState(QSharedPointer<IEGamePlayState>::create(game));

        this->setEnabled(false);
    });

    connect(&game, &IEGame::stateChanged, this, [this](QSharedPointer<IEGameState> state)
            {
                if(dynamic_cast<IEGameStopState*>(&(*state)))
                    this->setEnabled(true);
            });
}

ToggleGamePlayAction::~ToggleGamePlayAction()
{

}
