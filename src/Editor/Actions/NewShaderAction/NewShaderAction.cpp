#include "NewShaderAction.h"
#include "IENameManager.h"
#include "IEShaderManager.h"
#include "IEFile.h"
#include <QFileDialog>

NewShaderAction::NewShaderAction(IENameManager* nameManager, IEShaderManager* shaderManager,
                                 InputKey* shortcut, QObject* parent) :
    MenuAction("New", shortcut, parent)
{
    connect(this, &NewShaderAction::triggered, this, [nameManager, shaderManager]()
    {
        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "New Shader...",
                                                    ".",
                                                    "GLSL Files(*.glsl)");
        if(path.isEmpty())
            return;

        QString vSrc = "[VERTEX]\n#version 430 core\n\nvoid main()\n{\n\t\n}\n\n";
        QString fSrc = "[FRAGMENT]\n#version 430 core\n\nvoid main()\n{\n\t\n}\n";
        IEFile::write(path, (vSrc + fSrc));

        QString name = "";
        unsigned long long id = 0;
        std::tie(id, name) = nameManager->hashString(path);

        nameManager->add(id, new QString(name));

        auto shader = new IEShader(id, path);
        shader->build();

        shaderManager->add(id, shader);
    });
}
