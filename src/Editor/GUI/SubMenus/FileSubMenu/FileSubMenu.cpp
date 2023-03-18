#include "FileSubMenu.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "NewGameFileAction.h"
#include "OpenGameFileAction.h"
#include "SaveGameFileAction.h"
#include "SaveAsGameFileAction.h"
#include "ToggleWindowAction.h"
#include "QuitAppAction.h"

FileSubMenu::FileSubMenu(QWidget* parent) :
    SubMenu("File", parent)
{

}

FileSubMenu::~FileSubMenu()
{

}

void FileSubMenu::setupActions(const AppStartEvent& event)
{
    auto* input = event.getEditor()->getInput();
    auto windowManager = event.getEditor()->getUi()->getWindowManager();
    auto applicationWindow = event.getAppWindow();

    appendAction("New File", new NewGameFileAction(applicationWindow, input->getConfigKey("New File"), this));
    appendAction("Open File", new OpenGameFileAction(applicationWindow, input->getConfigKey("Open File"), this));
    appendAction("Save File", new SaveGameFileAction(applicationWindow, input->getConfigKey("Save File"), this));
    appendAction("Save File As", new SaveAsGameFileAction(applicationWindow, input->getConfigKey("Save File As"), this));
    this->addSeparator();
    appendAction("Options", new ToggleWindowAction("Options", input->getConfigKey("Options"), windowManager->getValue("Options"), this));
    appendAction("Quit", new QuitAppAction(input->getConfigKey("Quit"), this));
}
