#include "GameSubMenu.h"
#include "ToggleGamePlayAction.h"
#include "ToggleGameStopAction.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"

GameSubMenu::GameSubMenu(QWidget* parent) :
    SubMenu("Game", parent)
{

}

GameSubMenu::~GameSubMenu()
{

}

void GameSubMenu::setupActions(const AppStartEvent& event)
{
    auto* game = event.getGame();
    auto* input = event.getEditor()->getInput();

    appendAction("Play", new ToggleGamePlayAction(*game, input->getConfigKey("Toggle Play"), this));
    appendAction("Stop", new ToggleGameStopAction(*game, input->getConfigKey("Toggle Stop"), this));
}
