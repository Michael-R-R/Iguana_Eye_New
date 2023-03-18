#include "EActionStartup.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "ToggleEditorUiAction.h"

void EActionStartup::startup(const AppStartEvent& event)
{
    auto* input = event.getEditor()->getInput();
    auto* ui = event.getEditor()->getUi();
    auto* applicationWindow = event.getAppWindow();

    applicationWindow->addAction(new ToggleEditorUiAction(input->getConfigKey("Toggle Ui"), ui, applicationWindow));
}
