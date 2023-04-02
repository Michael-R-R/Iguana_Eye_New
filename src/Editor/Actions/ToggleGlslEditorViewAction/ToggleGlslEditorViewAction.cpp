#include "ToggleGlslEditorViewAction.h"
#include "EWGlslEditor.h"

ToggleGlslEditorViewAction::ToggleGlslEditorViewAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Vertical/Horizontal", shortcut, parent)
{
    connect(this, &BaseAction::triggered, this, [editor]()
    {
        editor->changeView();
    });
}
