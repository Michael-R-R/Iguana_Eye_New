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
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto time = event.getGame()->getIETime();

    appendAction("Render", new ToggleGameRenderAction(inputContainer->fetchValue("Toggle Rendering"), time, this));
    appendAction("Update", new ToggleGameUpdateAction(inputContainer->fetchValue("Toggle Updating"), time, this));
}
