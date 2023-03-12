#include "CompileShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"

CompileShaderAction::CompileShaderAction(EWGlslEditor* editor, IEShaderManager& manager,
                                         InputKey& shortcut, QObject* parent) :
    MenuAction("Compile", shortcut, parent)
{
    this->setEnabled(false);

    connect(this, &CompileShaderAction::triggered, this, [editor, &manager]()
    {
        unsigned long long id = editor->getShaderComboBox()->getSelectedId();
        auto& shader = manager.getValue(id);
        if(shader.getId() == 0)
            return;

        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();

        shader.setVertexSrc(vSrc);
        shader.setFragmentSrc(fSrc);

        shader.build();
    });

    connect(editor->getShaderComboBox(), &EWShaderComboBox::currentIndexChanged, this, [this](int index)
    {
        this->setEnabled((index > 0));
    });
}
