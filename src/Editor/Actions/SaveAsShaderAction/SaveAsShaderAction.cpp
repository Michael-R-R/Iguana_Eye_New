#include "SaveAsShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderExport.h"
#include <QFileDialog>

SaveAsShaderAction::SaveAsShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Save As", shortcut, parent)
{
    connect(this, &SaveAsShaderAction::triggered, this, [editor]()
            {
                QString path = QFileDialog::getSaveFileName(nullptr,
                                                            "Glsl Save As...",
                                                            "./resources",
                                                            "Glsl File(*.glsl)");
                if(path.isEmpty())
                    return;

                editor->saveAsGlslFile(path);
            });
}
