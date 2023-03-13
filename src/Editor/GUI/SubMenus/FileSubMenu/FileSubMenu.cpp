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
    auto& inputContainer = event.getEditor().getInput().getInputContainer();
    auto& windowManager = event.getEditor().getUi().getWindowManager();
    auto* applicationWindow = event.getAppWindow();

    appendAction("New File", std::move(std::make_unique<NewGameFileAction>(applicationWindow, inputContainer.getValue("New File"), this)));
    appendAction("Open File", std::move(std::make_unique<OpenGameFileAction>(applicationWindow, inputContainer.getValue("Open File"), this)));
    appendAction("Save File", std::move(std::make_unique<SaveGameFileAction>(applicationWindow, inputContainer.getValue("Save File"), this)));
    appendAction("Save File As", std::move(std::make_unique<SaveAsGameFileAction>(applicationWindow, inputContainer.getValue("Save File As"), this)));
    this->addSeparator();
    appendAction("Options", std::move(std::make_unique<ToggleWindowAction>("Options", inputContainer.getValue("Options"), windowManager.getValue("Options"), this)));
    appendAction("Quit", std::move(std::make_unique<QuitAppAction>(inputContainer.getValue("Quit"), this)));
}
