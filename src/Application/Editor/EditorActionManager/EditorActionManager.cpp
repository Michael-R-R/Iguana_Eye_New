#include "EditorActionManager.h"
#include "AppStartEvent.h"
#include "ToggleUiAction.h"

EditorActionManager::EditorActionManager(QObject* parent) :
    QObject(parent)
{

}

EditorActionManager::~EditorActionManager()
{

}

void EditorActionManager::setup(const AppStartEvent& event)
{
    auto input = event.editor()->getInput();
    auto inputContainer = input->getInputContainer();
    auto ui = event.editor()->getUi();
    auto applicationWindow = event.applicationWindow();

    applicationWindow->addAction(new ToggleUiAction(inputContainer->fetchValue("Toggle Ui"), ui, this));
}
