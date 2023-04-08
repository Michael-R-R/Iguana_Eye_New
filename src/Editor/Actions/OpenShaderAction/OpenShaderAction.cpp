#include "OpenShaderAction.h"
#include "IEShaderManager.h"
#include "IEGlslImporter.h"
#include "IEHash.h"
#include "IEFile.h"
#include "IESerialize.h"
#include <QFileDialog>

OpenShaderAction::OpenShaderAction(IEShaderManager& shaderManager,
                                   InputKey& shortcut, QObject* parent) :
    BaseAction("Open", shortcut, parent)
{
    connect(this, &OpenShaderAction::triggered, this, [&shaderManager]()
    {
        QString path = QFileDialog::getOpenFileName(nullptr,
                                                    "Open Shader...",
                                                    "./resources",
                                                    "Shader(*.ieshader)");
        if(path.isEmpty())
            return;

        unsigned long long id = IEHash::Compute(path);
        if(shaderManager.doesExist(id))
            return;

        auto shader = QSharedPointer<IEShader>::create();
        if(!IESerialize::read<IEShader>(path, &(*shader)))
            return;

        shader->build();
        shaderManager.add(id, shader);
    });
}
