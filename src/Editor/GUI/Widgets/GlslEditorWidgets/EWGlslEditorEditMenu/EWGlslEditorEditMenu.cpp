#include "EWGlslEditorEditMenu.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEScene.h"
#include "Editor.h"
#include "EInput.h"
#include "EWGlslEditor.h"
#include "CompileShaderAction.h"

EWGlslEditorEditMenu::EWGlslEditorEditMenu(QWidget* parent) :
    SubMenu("Edit", parent)
{

}

void EWGlslEditorEditMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto* input = event.getEditor()->getInput();
    auto& shaderManager = IEScene::instance().getShaderManager();

    appendAction("Compile", new CompileShaderAction(editor, shaderManager, input->getConfigKey(""), this));
}
