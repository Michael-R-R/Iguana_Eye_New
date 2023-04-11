#include "CompileShaderAction.h"
#include "EWGlslEditor.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEHash.h"

CompileShaderAction::CompileShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Compile", shortcut, parent)
{
    this->setEnabled(false);

    connect(this, &CompileShaderAction::triggered, this, [editor]()
            {
                auto& shaderManager = IEScene::instance().getShaderManager();

                unsigned long long id = IEHash::Compute(editor->getCurrShaderPath());
                auto shader = shaderManager.value(id);
                if(!shader)
                    return;

                QString vSrc = editor->getVertexSource();
                QString fSrc = editor->getFragmentSource();

                shader->setVertexSrc(vSrc);
                shader->setFragmentSrc(fSrc);

                shader->build();
            });

    connect(editor, &EWGlslEditor::glslPathChanged, this, [this](const QString& path)
            {
                this->setEnabled(!path.isEmpty());
            });
}
