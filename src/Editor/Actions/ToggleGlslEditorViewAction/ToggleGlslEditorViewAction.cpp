#include "ToggleGlslEditorViewAction.h"
#include "EWGlslEditor.h"

ToggleGlslEditorViewAction::ToggleGlslEditorViewAction(EWGlslEditor* editor, InputKey* shortcut, QObject* parent) :
    MenuAction("Vertical/Horizontal", shortcut, parent)
{
    connect(this, &MenuAction::triggered, this, [editor]()
    {
        editor->changeView();
    });
}
