#include "FileSubMenu.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EGUI.h"
#include "EInput.h"
#include "NewGameFileAction.h"
#include "OpenGameFileAction.h"
#include "SaveGameFileAction.h"
#include "SaveAsGameFileAction.h"
#include "ToggleWindowAction.h"
#include "QuitAppAction.h"
#include "IEGame.h"
#include "IEGamePlayState.h"
#include "IEGameStopState.h"

FileSubMenu::FileSubMenu(QWidget* parent) :
    SubMenu("File", parent)
{

}

FileSubMenu::~FileSubMenu()
{

}

void FileSubMenu::startup(const AppStartEvent& event)
{
    auto* input = event.getEditor()->getInput();
    auto windowManager = event.getEditor()->getUi()->getWindowManager();
    auto applicationWindow = event.getAppWindow();

    appendAction("New File", new NewGameFileAction(applicationWindow, input->getConfigKey("New File"), this));
    appendAction("Open File", new OpenGameFileAction(applicationWindow, input->getConfigKey("Open File"), this));
    appendAction("Save File", new SaveGameFileAction(applicationWindow, input->getConfigKey("Save File"), this));
    appendAction("Save File As", new SaveAsGameFileAction(applicationWindow, input->getConfigKey("Save File As"), this));
    this->addSeparator();
    appendAction("Options", new ToggleWindowAction("Options", input->getConfigKey("Options"), windowManager->value("Options"), this));
    appendAction("Quit", new QuitAppAction(input->getConfigKey("Quit"), this));

    setupConnections(event);
}

void FileSubMenu::setupConnections(const AppStartEvent& event)
{
    connect(event.getGame(), &IEGame::stateChanged, this, [this](QSharedPointer<IEGameState> state)
            {
                if(dynamic_cast<IEGamePlayState*>(&(*state)))
                    this->setAllEnabled(false);
                else if(dynamic_cast<IEGameStopState*>(&(*state)))
                    this->setAllEnabled(true);
            });
}
