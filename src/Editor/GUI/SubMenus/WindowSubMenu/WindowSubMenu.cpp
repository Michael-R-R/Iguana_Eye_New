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
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto windowManager = event.getEditor()->getUi()->getWindowManager();

    appendAction("GLSL Editor", new ToggleWindowAction("GLSL Editor",
                                                       inputContainer->getValue("GLSL Editor"),
                                                       windowManager->getValue("GLSL Editor"),
                                                       this));
}
