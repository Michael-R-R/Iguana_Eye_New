#include "NewShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderExport.h"
#include <QFileDialog>

NewShaderAction::NewShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("New", shortcut, parent)
{
    connect(this, &NewShaderAction::triggered, this, [editor]()
    {
        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "New GLSL...",
                                                    "./resources",
                                                    "GLSL File(*.glsl)");
        if(path.isEmpty())
            return;

        editor->newGlslFile(path);
    });
}
