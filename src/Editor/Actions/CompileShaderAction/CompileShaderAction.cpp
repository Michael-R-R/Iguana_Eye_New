#include "CompileShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"

CompileShaderAction::CompileShaderAction(EWGlslEditor* editor, IEShaderManager* manager,
                                         InputKey* shortcut, QObject* parent) :
    MenuAction("Compile", shortcut, parent)
{
    connect(this, &CompileShaderAction::triggered, this, [editor, manager]()
    {
        unsigned long long id = editor->getShaderComboBox()->getSelectedId();
        IEShader* shader = manager->getValue(id);
        if(!shader)
            return;

        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();

        shader->setVertexSrc(vSrc);
        shader->setFragmentSrc(fSrc);

        shader->build();
    });
}
