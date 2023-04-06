#include "EWGlslEditorViewMenu.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "EInput.h"
#include "EWGlslEditor.h"
#include "ToggleGlslEditorViewAction.h"

EWGlslEditorViewMenu::EWGlslEditorViewMenu(QWidget* parent) :
    SubMenu("View", parent)
{

}

void EWGlslEditorViewMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto* input = event.getEditor()->getInput();

    appendAction("Vertical/Horizontal", new ToggleGlslEditorViewAction(editor, input->getConfigKey(""), this));
}
