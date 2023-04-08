#include "NewShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IEFile.h"
#include <QFileDialog>

NewShaderAction::NewShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                                 InputKey& shortcut, QObject* parent) :
    BaseAction("New", shortcut, parent)
{
    connect(this, &NewShaderAction::triggered, this, [editor, &shaderManager]()
    {
        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "New Shader...",
                                                    "./resources",
                                                    "Shader(*.ieshader)");
        if(path.isEmpty())
            return;

        editor->clearAll();

        unsigned long long id = IEHash::Compute(path);
        if(shaderManager.doesExist(id))
        {
            auto* shader = shaderManager.value(id);
            shader->setVertexSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
            shader->setFragmentSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
            shader->build();
        }
        else
        {
            auto shader = std::make_unique<IEShader>(path);
            shader->build();
            shaderManager.add(id, std::move(shader));
        }

        QString vSrc = "[VERTEX]\n#version 430 core\n\nvoid main()\n{\n\t\n}\n\n";
        QString fSrc = "[FRAGMENT]\n#version 430 core\n\nvoid main()\n{\n\t\n}\n\n";
        IEFile::write(path, vSrc + fSrc);
    });
}
