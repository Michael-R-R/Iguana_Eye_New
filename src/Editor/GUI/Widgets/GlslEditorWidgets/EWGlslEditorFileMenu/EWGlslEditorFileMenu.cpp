#include "EWGlslEditorFileMenu.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "Editor.h"
#include "NewShaderAction.h"

EWGlslEditorFileMenu::EWGlslEditorFileMenu(QWidget* parent) :
    SubMenu("File", parent)
{

}

void EWGlslEditorFileMenu::startup(const AppStartEvent& event)
{
    auto inputContainer = event.getEditor()->getInput()->getInputContainer();
    auto nameManager = event.getGame()->getIEScene()->getNameManager();
    auto shaderManager = event.getGame()->getIEScene()->getShaderManager();

    appendAction("New", new NewShaderAction(nameManager, shaderManager, inputContainer->getValue(""), this));
}
