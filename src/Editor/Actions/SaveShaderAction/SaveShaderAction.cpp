#include "SaveShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEFile.h"

SaveShaderAction::SaveShaderAction(EWGlslEditor* editor, IEShaderManager* shaderManager,
                                   InputKey* shortcut, QObject* parent) :
    MenuAction("Save", shortcut, parent)
{
    connect(this, &SaveShaderAction::triggered, this, [editor, shaderManager]()
    {
        unsigned long long id = editor->getShaderComboBox()->getSelectedId();
        if(id == 0)
            return;

        auto shader = shaderManager->getValue(id);
        if(!shader)
            return;

        QString path = shader->getFilePath();
        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();
        QString content = "[VERTEX]\n" + vSrc + "[FRAGMENT]\n" + fSrc;

        IEFile::write(path, content);

        shader->setVertexSrc(vSrc);
        shader->setFragmentSrc(fSrc);
        shader->build();
    });
}
