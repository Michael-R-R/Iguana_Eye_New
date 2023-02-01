#include "GameSubMenu.h"
#include "AppStartEvent.h"
#include "ToggleGameRenderAction.h"
#include "ToggleGameUpdateAction.h"

GameSubMenu::GameSubMenu(QWidget* parent) :
    SubMenu("Game", parent)
{

}

GameSubMenu::~GameSubMenu()
{

}

void GameSubMenu::setupActions(const AppStartEvent& event)
{
    auto inputContainer = event.editor()->getInput()->getInputContainer();
    auto time = event.game()->getTime();

    appendAction("Render", new ToggleGameRenderAction(inputContainer->fetchValue("Toggle Rendering"), time, this));
    appendAction("Update", new ToggleGameUpdateAction(inputContainer->fetchValue("Toggle Updating"), time, this));
}
