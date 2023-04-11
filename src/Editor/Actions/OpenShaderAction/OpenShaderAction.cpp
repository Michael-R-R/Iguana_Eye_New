#include "OpenShaderAction.h"
#include "EWGlslEditor.h"
#include <QFileDialog>

OpenShaderAction::OpenShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Open", shortcut, parent)
{
    connect(this, &OpenShaderAction::triggered, this, [editor]()
            {
                QString path = QFileDialog::getOpenFileName(nullptr,
                                                            "Open GLSL...",
                                                            "./resources",
                                                            "GLSL File(*.glsl)");
                if(path.isEmpty())
                    return;

                editor->openGlslFile(path);
            });
}
