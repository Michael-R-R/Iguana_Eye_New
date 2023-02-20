#include "NewShaderAction.h"
#include "IENameManager.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IESerialize.h"
#include <QFileDialog>

NewShaderAction::NewShaderAction(IENameManager* nameManager, IEShaderManager* shaderManager,
                                 InputKey* shortcut, QObject* parent) :
    MenuAction("New", shortcut, parent)
{
    connect(this, &NewShaderAction::triggered, this, [nameManager, shaderManager]()
    {
        QString path = QFileDialog::getSaveFileName(nullptr,
                                                    "New Shader...",
                                                    "./resources",
                                                    "Shader(*.ieshader)");
        if(path.isEmpty())
            return;

        auto id = IEHash::Compute(path);
        if(nameManager->doesExist(id))
            shaderManager->remove(id);
        else
            nameManager->add(id, new QString(path));

        auto shader = new IEShader(path, id);
        shader->build();

        shaderManager->add(id, shader);

        IESerialize::write<IEShader>(path, shader);
    });
}
