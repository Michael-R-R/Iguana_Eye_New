#include "EWGlslEditorFileMenu.h"
#include "AppStartEvent.h"
#include "EWGlslEditor.h"
#include "IEGame.h"
#include "IEScene.h"
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
    auto& shaderManager = event.getGame()->getIEScene().getShaderManager();

    appendAction("New Shader", new NewShaderAction(editor, shaderManager, input->getConfigKey(""), this));
    appendAction("Open Shader", new OpenShaderAction(shaderManager, input->getConfigKey(""), this));
    appendAction("Save Shader", new SaveShaderAction(editor, shaderManager, input->getConfigKey(""), this));
    appendAction("Save As Shader", new SaveAsShaderAction(editor, shaderManager, input->getConfigKey(""), this));
}
