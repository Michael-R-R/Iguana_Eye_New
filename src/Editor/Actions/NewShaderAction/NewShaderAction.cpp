#include "NewShaderAction.h"
#include "EWGlslEditor.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IESerialize.h"
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
        QSharedPointer<IEShader> shader = nullptr;
        if(shaderManager.doesExist(id))
        {
            shader = shaderManager.value(id);
        }
        else
        {
            shader = QSharedPointer<IEShader>::create(path);
            shaderManager.add(id, shader);
        }

        shader->setVertexSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
        shader->setFragmentSrc("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n");
        shader->build();

        IESerialize::write<IEShader>(path, &(*shader));
    });
}
