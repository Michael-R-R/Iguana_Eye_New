#include "SaveAsShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IEFile.h"
#include <QFileDialog>

SaveAsShaderAction::SaveAsShaderAction(EWGlslEditor* editor, IEShaderManager* shaderManager,
                                       InputKey* shortcut, QObject* parent) :
    MenuAction("Save As", shortcut, parent)
{
    connect(this, &SaveAsShaderAction::triggered, this, [editor, shaderManager]()
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

        QString vSrc = editor->getVertSrcEditor()->getTextContent();
        QString fSrc = editor->getFragSrcEditor()->getTextContent();
        QString content = "[VERTEX]\n" + vSrc + "[FRAGMENT]\n" + fSrc;
        IEFile::write(path, content);

        id = IEHash::Compute(path);
        if(shaderManager->doesExist(id))
            return;

        auto shader = new IEShader(path, id);
        shader->setVertexSrc(vSrc);
        shader->setFragmentSrc(fSrc);
        shader->build();
        shaderManager->add(id, shader);

        editor->getShaderComboBox()->selectShader(id);
    });
}
