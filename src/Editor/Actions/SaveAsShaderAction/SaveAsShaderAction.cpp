#include "SaveAsShaderAction.h"
#include "EWGlslEditor.h"
#include "IEGlslExporter.h"
#include <QFileDialog>

SaveAsShaderAction::SaveAsShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Save As", shortcut, parent)
{
    this->setEnabled(false);

    connect(this, &SaveAsShaderAction::triggered, this, [editor]()
            {
                QString path = QFileDialog::getSaveFileName(nullptr,
                                                            "Save As Shader...",
                                                            "./resources",
                                                            "Shaders(*.ieshader)");
                if(path.isEmpty())
                    return;

                QString vSrc = editor->getVertexSource();
                QString fSrc = editor->getFragmentSource();

                IEGlslExporter::exportGlsl(path, vSrc, fSrc);
            });

    connect(editor, &EWGlslEditor::glslPathChanged, this, [this](const QString& path)
            {
                this->setEnabled(!path.isEmpty());
            });
}
