#include "EWGlslEditorFileMenu.h"
#include "AppStartEvent.h"
#include "EWGlslEditor.h"
#include "IEGame.h"
#include "IEScene.h"
#include "Editor.h"
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
    auto& inputContainer = event.getEditor().getInput().getInputContainer();
    auto& shaderManager = event.getGame().getIEScene().getShaderManager();

    appendAction("New Shader", std::move(std::make_unique<NewShaderAction>(editor, shaderManager, inputContainer.getValue(""), this)));
    appendAction("Open Shader", std::move(std::make_unique<OpenShaderAction>(shaderManager, inputContainer.getValue(""), this)));
    appendAction("Save Shader", std::move(std::make_unique<SaveShaderAction>(editor, shaderManager, inputContainer.getValue(""), this)));
    appendAction("Save As Shader", std::move(std::make_unique<SaveAsShaderAction>(editor, shaderManager, inputContainer.getValue(""), this)));
}
