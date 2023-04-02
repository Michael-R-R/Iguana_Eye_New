#include "SaveAsShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IEFile.h"
#include "IEGlslImporter.h"
#include <QFileDialog>

SaveAsShaderAction::SaveAsShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                                       InputKey& shortcut, QObject* parent) :
    BaseAction("Save As", shortcut, parent)
{
    this->setEnabled(false);

    connect(this, &SaveAsShaderAction::triggered, this, [editor, &shaderManager]()
    {
        unsigned long long id = editor->getShaderComboBox()->getSelectedId();
        if(id == 0)
            return;

        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "Save As Shader...",
                                                    "./resources",
                                                    "Shaders(*.glsl)");
        if(path.isEmpty())
            return;

        editor->saveContentToFile(path);

        id = IEHash::Compute(path);
        if(shaderManager.doesExist(id))
            return;

        std::unique_ptr<IEShader> shader = std::make_unique<IEShader>(path, id);
        if(!IEGlslImporter::importGlsl(path, *shader))
            return;

        shader->build();
        shaderManager.add(id, std::move(shader));
    });

    connect(editor->getShaderComboBox(), &EWShaderComboBox::currentIndexChanged, this, [this](int index)
    {
        this->setEnabled((index > 0));
    });
}
