#include "EWGlslEditorEditMenu.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEScene.h"
#include "Editor.h"
#include "EWGlslEditor.h"
#include "CompileShaderAction.h"

EWGlslEditorEditMenu::EWGlslEditorEditMenu(QWidget* parent) :
    SubMenu("Edit", parent)
{

}

void EWGlslEditorEditMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto& inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto shaderManager = event.getGame()->getIEScene().getShaderManager();

    appendAction("Compile", new CompileShaderAction(editor, shaderManager, inputContainer.getValue(""), this));
}
