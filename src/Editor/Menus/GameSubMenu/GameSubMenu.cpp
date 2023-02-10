#include "GameSubMenu.h"
#include "ToggleGameRenderAction.h"
#include "ToggleGameUpdateAction.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "Game.h"

GameSubMenu::GameSubMenu(QWidget* parent) :
    SubMenu("Game", parent)
{

}

GameSubMenu::~GameSubMenu()
{

}

void GameSubMenu::setupActions(const AppStartEvent& event)
{
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto time = event.getGame()->getIETime();

    appendAction("Render", new ToggleGameRenderAction(inputContainer->fetchValue("Toggle Rendering"), time, this));
    appendAction("Update", new ToggleGameUpdateAction(inputContainer->fetchValue("Toggle Updating"), time, this));
}
