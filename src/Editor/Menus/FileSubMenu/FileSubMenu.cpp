#include "FileSubMenu.h"
#include "AppStartEvent.h"
#include "LoadGameAction.h"
#include "SaveGameAction.h"
#include "SaveAsGameAction.h"
#include "AppOptionsAction.h"
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
    auto inputContainer = event.editor()->getInput()->getInputContainer();
    auto windowManager = event.editor()->getUi()->getWindowManager();
    auto applicationWindow = event.applicationWindow();

    appendAction("Open", new LoadGameAction(applicationWindow, inputContainer->fetchValue("Open"), this));
    appendAction("Save", new SaveGameAction(applicationWindow, inputContainer->fetchValue("Save"), this));
    appendAction("Save As", new SaveAsGameAction(applicationWindow, inputContainer->fetchValue("Save As"), this));
    this->addSeparator();
    appendAction("Options", new AppOptionsAction(inputContainer->fetchValue("Options"), windowManager, this));
    appendAction("Quit", new QuitAppAction(inputContainer->fetchValue("Quit"), this));
}
