#include "SaveShaderAction.h"
#include "EWGlslEditor.h"

SaveShaderAction::SaveShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Save", shortcut, parent)
{
    connect(this, &SaveShaderAction::triggered, this, [this, editor]()
            {
                editor->saveGlslFile();
            });
}
