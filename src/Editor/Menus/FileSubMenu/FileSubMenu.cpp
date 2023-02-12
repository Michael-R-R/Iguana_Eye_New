#include "FileSubMenu.h"
#include "NewGameFileAction.h"
#include "OpenGameFileAction.h"
#include "SaveGameFileAction.h"
#include "SaveAsGameFileAction.h"
#include "AppOptionsAction.h"
#include "QuitAppAction.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"

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

    appendAction("New File", new NewGameFileAction(applicationWindow, inputContainer->fetchValue("New File"), this));
    appendAction("Open File", new OpenGameFileAction(applicationWindow, inputContainer->fetchValue("Open File"), this));
    appendAction("Save File", new SaveGameFileAction(applicationWindow, inputContainer->fetchValue("Save File"), this));
    appendAction("Save File As", new SaveAsGameFileAction(applicationWindow, inputContainer->fetchValue("Save File As"), this));
    this->addSeparator();
    appendAction("Options", new AppOptionsAction(inputContainer->fetchValue("Options"), windowManager, this));
    appendAction("Quit", new QuitAppAction(inputContainer->fetchValue("Quit"), this));
}
