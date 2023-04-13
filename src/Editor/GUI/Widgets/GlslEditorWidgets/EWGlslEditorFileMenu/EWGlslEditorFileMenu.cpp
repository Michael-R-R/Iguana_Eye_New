#include "EWGlslEditorFileMenu.h"
#include "EWGlslEditor.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "EInput.h"
#include "NewShaderAction.h"
#include "OpenShaderAction.h"
#include "SaveShaderAction.h"
#include "SaveAsShaderAction.h"

EWGlslEditorFileMenu::EWGlslEditorFileMenu(QWidget* parent) :
    SubMenu("File", parent)
{

}

void EWGlslEditorFileMenu::startup(EWGlslEditor* glEditor)
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* input = editor->getInput();

    appendAction("New Shader", new NewShaderAction(glEditor, input->getConfigKey(""), this));
    appendAction("Open Shader", new OpenShaderAction(glEditor, input->getConfigKey(""), this));
    appendAction("Save Shader", new SaveShaderAction(glEditor, input->getConfigKey(""), this));
    appendAction("Save As Shader", new SaveAsShaderAction(glEditor, input->getConfigKey(""), this));
}
