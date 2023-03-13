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
    auto& inputContainer = event.getEditor().getInput().getInputContainer();
    auto& time = event.getGame().getIETime();

    appendAction("Render", std::move(std::make_unique<ToggleGameRenderAction>(inputContainer.getValue("Toggle Rendering"), time, this)));
    appendAction("Update", std::move(std::make_unique<ToggleGameUpdateAction>(inputContainer.getValue("Toggle Updating"), time, this)));
}
