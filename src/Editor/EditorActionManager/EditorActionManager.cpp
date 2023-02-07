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
    auto input = event.getEditor()->getInput();
    auto inputContainer = input->getInputContainer();
    auto ui = event.getEditor()->getUi();
    auto applicationWindow = event.getApplicationWindow();

    applicationWindow->addAction(new ToggleUiAction(inputContainer->fetchValue("Toggle Ui"), ui, this));
}
