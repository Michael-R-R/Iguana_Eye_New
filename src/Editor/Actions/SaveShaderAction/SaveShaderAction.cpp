#include "SaveShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEFile.h"

SaveShaderAction::SaveShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                                   InputKey& shortcut, QObject* parent) :
    MenuAction("Save", shortcut, parent),
    isShaderActive(false)
{
    this->setEnabled(false);

    connect(this, &SaveShaderAction::triggered, this, [this, editor, &shaderManager]()
    {
        unsigned long long id = editor->getShaderComboBox()->getSelectedId();
        if(id == 0)
            return;

        auto* shader = shaderManager.value(id);
        if(!shader)
            return;

        const QString& path = shader->getFilePath();
        editor->saveContentToFile(path);

        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();

        shader->setVertexSrc(vSrc);
        shader->setFragmentSrc(fSrc);
    });

    connect(editor->getShaderComboBox(), &EWShaderComboBox::currentIndexChanged, this, [this](int index)
    {
        isShaderActive = (index > 0) ? true : false;
        if(!isShaderActive)
            this->setEnabled(false);
    });

    connect(editor->getVertSrcEditor(), &EWGlslSrcEditor::modified, this, [this, editor](const bool val)
    {
        bool status = (isShaderActive) ? val : false;
        this->setEnabled(status);
    });

    connect(editor->getFragSrcEditor(), &EWGlslSrcEditor::modified, this, [this, editor](const bool val)
    {
        bool status = (isShaderActive) ? val : false;
        this->setEnabled(status);
    });
}
