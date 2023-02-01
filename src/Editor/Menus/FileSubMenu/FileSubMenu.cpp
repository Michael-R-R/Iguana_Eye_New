#include "FileSubMenu.h"
#include "AppStartEvent.h"
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

    appendAction("Options", new AppOptionsAction(inputContainer->fetchValue("Options"), windowManager, this));
    appendAction("Quit", new QuitAppAction(inputContainer->fetchValue("Quit"), this));
}
