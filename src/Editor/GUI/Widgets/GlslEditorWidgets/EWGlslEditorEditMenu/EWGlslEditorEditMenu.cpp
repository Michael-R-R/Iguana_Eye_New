#include "EWGlslEditorEditMenu.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EInput.h"
#include "EWGlslEditor.h"
#include "CompileShaderAction.h"

EWGlslEditorEditMenu::EWGlslEditorEditMenu(QWidget* parent) :
    SubMenu("Edit", parent)
{

}

void EWGlslEditorEditMenu::startup(EWGlslEditor* glEditor)
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* input = editor->getInput();

    appendAction("Compile", new CompileShaderAction(glEditor, input->getConfigKey(""), this));
}
