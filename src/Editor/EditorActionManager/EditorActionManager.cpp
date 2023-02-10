#include "EditorActionManager.h"
#include "ToggleUiAction.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"

EditorActionManager::EditorActionManager(QObject* parent) :
    QObject(parent)
{

}

EditorActionManager::~EditorActionManager()
{

}

void EditorActionManager::setup(const AppStartEvent& event)
{
    auto input = event.getEditor()->getInput();
    auto inputContainer = input->getInputContainer();
    auto ui = event.getEditor()->getUi();
    auto applicationWindow = event.getAppWindow();

    applicationWindow->addAction(new ToggleUiAction(inputContainer->fetchValue("Toggle Ui"), ui, this));
}
