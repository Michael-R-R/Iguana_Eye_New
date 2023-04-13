#include "FileSubMenu.h"
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

void FileSubMenu::startup()
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* input = editor->getInput();
    auto* ui = editor->getUi();
    auto* windowManager = ui->getWindowManager();

    appendAction("New File", new NewGameFileAction(&application, input->getConfigKey("New File"), this));
    appendAction("Open File", new OpenGameFileAction(&application, input->getConfigKey("Open File"), this));
    appendAction("Save File", new SaveGameFileAction(&application, input->getConfigKey("Save File"), this));
    appendAction("Save File As", new SaveAsGameFileAction(&application, input->getConfigKey("Save File As"), this));
    this->addSeparator();
    appendAction("Options", new ToggleWindowAction("Options", input->getConfigKey("Options"), windowManager->value("Options"), this));
    appendAction("Quit", new QuitAppAction(input->getConfigKey("Quit"), this));

    setupConnections();
}

void FileSubMenu::setupConnections()
{
    auto& application = ApplicationWindow::instance();
    auto game = application.getGame();

    connect(&(*game), &IEGame::stateChanged, this, [this](QSharedPointer<IEGameState> state)
            {
                if(dynamic_cast<IEGamePlayState*>(&(*state)))
                    this->setAllEnabled(false);
                else if(dynamic_cast<IEGameStopState*>(&(*state)))
                    this->setAllEnabled(true);
            });
}
