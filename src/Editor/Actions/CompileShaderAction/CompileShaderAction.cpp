#include "CompileShaderAction.h"
#include "EWGlslEditor.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
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
                auto* game = ApplicationWindow::instance().getGame();
                auto* scene = game->getSystem<IEScene>();
                auto* shaderManager = scene->getShaderManager();

                uint64_t id = IEHash::Compute(editor->getCurrShaderPath());
                auto* shader = shaderManager->value<IEShader>(id);
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
