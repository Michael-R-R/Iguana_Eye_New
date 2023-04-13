#include "EWGlslEditorViewMenu.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EInput.h"
#include "EWGlslEditor.h"
#include "ToggleGlslEditorViewAction.h"

EWGlslEditorViewMenu::EWGlslEditorViewMenu(QWidget* parent) :
    SubMenu("View", parent)
{

}

void EWGlslEditorViewMenu::startup(EWGlslEditor* glEditor)
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* input = editor->getInput();

    appendAction("Vertical/Horizontal", new ToggleGlslEditorViewAction(glEditor, input->getConfigKey(""), this));
}
