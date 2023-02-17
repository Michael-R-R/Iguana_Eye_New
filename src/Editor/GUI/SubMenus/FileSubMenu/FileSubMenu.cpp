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
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto windowManager = event.getEditor()->getUi()->getWindowManager();
    auto applicationWindow = event.getAppWindow();

    appendAction("New File", new NewGameFileAction(applicationWindow, inputContainer->getValue("New File"), this));
    appendAction("Open File", new OpenGameFileAction(applicationWindow, inputContainer->getValue("Open File"), this));
    appendAction("Save File", new SaveGameFileAction(applicationWindow, inputContainer->getValue("Save File"), this));
    appendAction("Save File As", new SaveAsGameFileAction(applicationWindow, inputContainer->getValue("Save File As"), this));
    this->addSeparator();
    appendAction("Options", new ToggleWindowAction("Options",
                                                   inputContainer->getValue("Options"),
                                                   windowManager->getValue("Options"),
                                                   this));
    appendAction("Quit", new QuitAppAction(inputContainer->getValue("Quit"), this));
}
