#include "WindowSubMenu.h"
#include "ToggleWindowAction.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EGUI.h"
#include "EInput.h"

WindowSubMenu::WindowSubMenu(QWidget* parent) :
    SubMenu("Window", parent)
{

}

void WindowSubMenu::setupActions()
{
    auto editor = ApplicationWindow::instance().getEditor();
    auto* input = editor->getInput();
    auto* ui = editor->getUi();
    auto* windowManager = ui->getWindowManager();

    appendAction("File Explorer", new ToggleWindowAction("File Explorer", input->getConfigKey("File Explorer"), windowManager->value("File Explorer"), this));
    appendAction("GLSL Editor", new ToggleWindowAction("GLSL Editor", input->getConfigKey("GLSL Editor"), windowManager->value("GLSL Editor"), this));
    appendAction("Message Log", new ToggleWindowAction("Message Log", input->getConfigKey("Message Log"), windowManager->value("Message Log"), this));
}
