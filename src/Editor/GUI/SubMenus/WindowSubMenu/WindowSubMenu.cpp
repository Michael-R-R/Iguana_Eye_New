#include "WindowSubMenu.h"
#include "AppStartEvent.h"
#include "ToggleWindowAction.h"
#include "Editor.h"

WindowSubMenu::WindowSubMenu(QWidget* parent) :
    SubMenu("Window", parent)
{

}

void WindowSubMenu::setupActions(const AppStartEvent& event)
{
    auto& inputContainer = event.getEditor().getInput().getInputContainer();
    auto* windowManager = event.getEditor().getUi().getWindowManager();

    appendAction("File Explorer", std::move(std::make_unique<ToggleWindowAction>("File Explorer", inputContainer.getValue("File Explorer"), windowManager->getValue("File Explorer"), this)));
    appendAction("GLSL Editor", std::move(std::make_unique<ToggleWindowAction>("GLSL Editor", inputContainer.getValue("GLSL Editor"), windowManager->getValue("GLSL Editor"), this)));
}
