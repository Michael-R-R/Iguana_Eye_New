#include "OpenShaderAction.h"
#include "IEShaderManager.h"
#include "IEGlslImporter.h"
#include "IEHash.h"
#include "IEFile.h"
#include <QFileDialog>

OpenShaderAction::OpenShaderAction(IEShaderManager& shaderManager,
                                   InputKey& shortcut, QObject* parent) :
    MenuAction("Open", shortcut, parent)
{
    connect(this, &OpenShaderAction::triggered, this, [&shaderManager]()
    {
        QString path = QFileDialog::getOpenFileName(nullptr,
                                                    "Open Shader...",
                                                    "./resources",
                                                    "Shader(*.glsl)");
        if(path.isEmpty())
            return;

        unsigned long long id = IEHash::Compute(path);
        if(shaderManager.doesExist(id))
            return;

        std::unique_ptr<IEShader> shader = std::make_unique<IEShader>(path, id);
        if(!IEGlslImporter::importGlsl(path, *shader))
            return;

        shader->build();
        shaderManager.add(id, std::move(shader));
    });
}
