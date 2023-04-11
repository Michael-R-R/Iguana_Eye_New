#include "SaveShaderAction.h"
#include "EWGlslEditor.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEHash.h"
#include "IEGlslExporter.h"

SaveShaderAction::SaveShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent) :
    BaseAction("Save", shortcut, parent),
    isVertexSrcDirty(false),
    isFragmentSrcDirty(false)
{
    this->setEnabled(false);

    connect(this, &SaveShaderAction::triggered, this, [this, editor]()
            {
                // Save source to file
                const QString& path = editor->getCurrShaderPath();
                QString vSrc = editor->getVertexSource();
                QString fSrc = editor->getFragmentSource();
                if(!IEGlslExporter::exportGlsl(path, vSrc, fSrc))
                    return;

                // Check is a shader exist to update
                auto& shaderManager = IEScene::instance().getShaderManager();
                unsigned long long id = IEHash::Compute(path);
                auto shader = shaderManager.value(id);
                if(!shader)
                    return;

                shader->setVertexSrc(vSrc);
                shader->setFragmentSrc(fSrc);
                shader->build();
            });

    connect(editor->getVertSrcEditor(), &EWGlslSrcEditor::modified, this, [this, editor](const bool val)
            {
                isVertexSrcDirty = val;
                this->setEnabled(isVertexSrcDirty || isFragmentSrcDirty);
            });

    connect(editor->getFragSrcEditor(), &EWGlslSrcEditor::modified, this, [this, editor](const bool val)
            {
                isFragmentSrcDirty = val;
                this->setEnabled(isVertexSrcDirty || isFragmentSrcDirty);
            });
}
