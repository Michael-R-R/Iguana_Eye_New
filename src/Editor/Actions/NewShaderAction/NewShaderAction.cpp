#include "NewShaderAction.h"
#include "EWGlslEditor.h"
#include "IEGlslExporter.h"
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

        QString vSrc = "#version 430 core\n\nint main()\n{\n\t\n}\n";
        QString fSrc = "#version 430 core\n\nint main()\n{\n\t\n}\n";
        IEGlslExporter::exportGlsl(path, vSrc, fSrc);

        editor->openGlslFile(path);
    });
}
