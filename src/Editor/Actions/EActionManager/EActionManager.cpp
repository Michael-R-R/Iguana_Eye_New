#include "EActionManager.h"
#include "ToggleEditorUiAction.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"

EActionManager::EActionManager(QObject* parent) :
    QObject(parent)
{

}

EActionManager::~EActionManager()
{

}

void EActionManager::setup(const AppStartEvent& event)
{
    auto input = event.getEditor()->getInput();
    auto inputContainer = input->getInputContainer();
    auto ui = event.getEditor()->getUi();
    auto applicationWindow = event.getAppWindow();

    applicationWindow->addAction(new ToggleEditorUiAction(inputContainer->fetchValue("Toggle Ui"), ui, this));
}
