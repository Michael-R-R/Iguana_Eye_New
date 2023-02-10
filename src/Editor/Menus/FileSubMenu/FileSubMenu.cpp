#include "FileSubMenu.h"
#include "LoadGameAction.h"
#include "SaveGameAction.h"
#include "SaveAsGameAction.h"
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

    appendAction("Open", new LoadGameAction(applicationWindow, inputContainer->fetchValue("Open"), this));
    appendAction("Save", new SaveGameAction(applicationWindow, inputContainer->fetchValue("Save"), this));
    appendAction("Save As", new SaveAsGameAction(applicationWindow, inputContainer->fetchValue("Save As"), this));
    this->addSeparator();
    appendAction("Options", new AppOptionsAction(inputContainer->fetchValue("Options"), windowManager, this));
    appendAction("Quit", new QuitAppAction(inputContainer->fetchValue("Quit"), this));
}
