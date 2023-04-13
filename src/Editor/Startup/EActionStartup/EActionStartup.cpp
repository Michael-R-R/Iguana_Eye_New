#include "EActionStartup.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EInput.h"
#include "ToggleEditorUiAction.h"

void EActionStartup::startup()
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* input = editor->getInput();
    auto* ui = editor->getUi();

    application.addAction(new ToggleEditorUiAction(input->getConfigKey("Toggle Ui"), ui, &(*editor)));
}
