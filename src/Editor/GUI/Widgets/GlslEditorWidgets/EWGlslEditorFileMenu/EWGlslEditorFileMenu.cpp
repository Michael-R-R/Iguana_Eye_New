#include "EWGlslEditorFileMenu.h"
#include "AppStartEvent.h"
#include "EWGlslEditor.h"
#include "IEGame.h"
#include "Editor.h"
#include "NewShaderAction.h"
#include "OpenShaderAction.h"
#include "SaveAsShaderAction.h"

EWGlslEditorFileMenu::EWGlslEditorFileMenu(QWidget* parent) :
    SubMenu("File", parent)
{

}

void EWGlslEditorFileMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto shaderManager = event.getGame()->getIEScene()->getShaderManager();

    appendAction("New Shader", new NewShaderAction(shaderManager, inputContainer->getValue(""), this));
    appendAction("Open Shader", new OpenShaderAction(shaderManager, inputContainer->getValue(""), this));
    appendAction("Save As Shader", new SaveAsShaderAction(editor, shaderManager, inputContainer->getValue(""), this));
}
