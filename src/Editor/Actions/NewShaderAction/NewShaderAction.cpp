#include "NewShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IEFile.h"
#include <QFileDialog>

NewShaderAction::NewShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                                 InputKey& shortcut, QObject* parent) :
    MenuAction("New", shortcut, parent)
{
    connect(this, &NewShaderAction::triggered, this, [editor, &shaderManager]()
    {
        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "New Shader...",
                                                    "./resources",
                                                    "Shader(*.glsl)");
        if(path.isEmpty())
            return;

        editor->clearAll();

        unsigned long long id = IEHash::Compute(path);
        IEShader* shader = nullptr;
        if(shaderManager.doesExist(id))
        {
            shader = shaderManager.getValue(id);
            shader->setVertexSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
            shader->setFragmentSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
            shader->build();
        }
        else
        {
            shader = new IEShader(path, id);
            shader->build();
            shaderManager.add(id, shader);
        }

        QString vSrc = "[VERTEX]\n" + shader->getVertexSrc();
        QString fSrc = "[FRAGMENT]\n" + shader->getFragmentSrc();
        IEFile::write(path, vSrc + fSrc);
    });
}
