#include "GameSubMenu.h"
#include "ToggleGameRenderAction.h"
#include "ToggleGameUpdateAction.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"
#include "IETime.h"

GameSubMenu::GameSubMenu(QWidget* parent) :
    SubMenu("Game", parent)
{

}

GameSubMenu::~GameSubMenu()
{

}

void GameSubMenu::setupActions(const AppStartEvent& event)
{
    auto* input = event.getEditor()->getInput();
    auto& time = event.getGame()->getIETime();

    appendAction("Render", new ToggleGameRenderAction(input->getConfigKey("Toggle Rendering"), time, this));
    appendAction("Update", new ToggleGameUpdateAction(input->getConfigKey("Toggle Updating"), time, this));
}
