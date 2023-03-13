#include "EWGlslEditorViewMenu.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "EWGlslEditor.h"
#include "ToggleGlslEditorViewAction.h"

EWGlslEditorViewMenu::EWGlslEditorViewMenu(QWidget* parent) :
    SubMenu("View", parent)
{

}

void EWGlslEditorViewMenu::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    auto& inputContainer = event.getEditor().getInput().getInputContainer();

    appendAction("Vertical/Horizontal", std::move(std::make_unique<ToggleGlslEditorViewAction>(editor, inputContainer.getValue("Invalid"), this)));
}
