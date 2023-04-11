#include "EWGlslEditorFileMenu.h"
#include "AppStartEvent.h"
#include "EWGlslEditor.h"
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

void EWGlslEditorFileMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto* input = event.getEditor()->getInput();

    appendAction("New Shader", new NewShaderAction(editor, input->getConfigKey(""), this));
    appendAction("Open Shader", new OpenShaderAction(editor, input->getConfigKey(""), this));
    appendAction("Save Shader", new SaveShaderAction(editor, input->getConfigKey(""), this));
    appendAction("Save As Shader", new SaveAsShaderAction(editor, input->getConfigKey(""), this));
}
