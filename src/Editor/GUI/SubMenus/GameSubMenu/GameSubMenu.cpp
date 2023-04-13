#include "GameSubMenu.h"
#include "ToggleGamePlayAction.h"
#include "ToggleGameStopAction.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EInput.h"
#include "IEGame.h"

GameSubMenu::GameSubMenu(QWidget* parent) :
    SubMenu("Game", parent)
{

}

GameSubMenu::~GameSubMenu()
{

}

void GameSubMenu::setupActions()
{
    auto& application = ApplicationWindow::instance();
    auto game = application.getGame();
    auto editor = application.getEditor();
    auto* input = editor->getInput();

    appendAction("Play", new ToggleGamePlayAction(game, input->getConfigKey("Toggle Play"), this));
    appendAction("Stop", new ToggleGameStopAction(game, input->getConfigKey("Toggle Stop"), this));
}
