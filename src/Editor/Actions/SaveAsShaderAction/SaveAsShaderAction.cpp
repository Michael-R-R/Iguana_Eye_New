#include "SaveAsShaderAction.h"
#include "EWGlslEditor.h"
#include "EWGlslSrcEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IESerialize.h"
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
                                                    "Shaders(*.ieshader)");
        if(path.isEmpty())
            return;

        id = IEHash::Compute(path);
        if(shaderManager.doesExist(id))
            return;

        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();

        auto shader = std::make_unique<IEShader>(path);
        shader->setVertexSrc(vSrc);
        shader->setFragmentSrc(fSrc);

        IESerialize::write<IEShader>(path, &(*shader));

        shader->build();
        shaderManager.add(id, std::move(shader));
    });

    connect(editor->getShaderComboBox(), &EWShaderComboBox::currentIndexChanged, this, [this](int index)
    {
        this->setEnabled((index > 0));
    });
}
