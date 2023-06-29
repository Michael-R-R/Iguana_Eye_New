#include "GlslFileHandler.h"
#include "EWGlslEditor.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEShader.h"
#include "IEShaderImport.h"
#include "IEShaderExport.h"
#include "IEFile.h"
#include "IEHash.h"
#include <QMessageBox>
#include <QFileDialog>

GlslFileHandler::GlslFileHandler(EWGlslEditor* editor) :
    glslEditor(editor)
{

}

GlslFileHandler::~GlslFileHandler()
{
    glslEditor = nullptr;
}

void GlslFileHandler::handleGlslNew(const QString& path)
{    if(path.isEmpty())
        return;

    if(askToSaveFile())
    {
        handleGlslSave(glslEditor->getCurrShaderPath());
    }

    QString vSrc = "#version 430 core\n\nint main()\n{\n\t\n}\n";
    QString fSrc = "#version 430 core\n\nint main()\n{\n\t\n}\n";
    IEShaderExport::exportShader(path, vSrc, fSrc);

    glslEditor->getCurrShaderNameLabel()->setText("");
    glslEditor->getCurrShaderPathLabel()->setText("");

    glslEditor->openGlslFile(path);
}

void GlslFileHandler::handleGlslOpen(const QString& path)
{
    if(path.isEmpty())
        return;

    if(askToSaveFile())
    {
        handleGlslSave(glslEditor->getCurrShaderPath());
    }

    QString vSrc = "";
    QString fSrc = "";
    IEShaderImport::importShader(path, vSrc, fSrc);

    QString name = IEFile::extractName(path);
    glslEditor->getCurrShaderNameLabel()->setText(name);
    glslEditor->getCurrShaderPathLabel()->setText(path);

    glslEditor->getVertSrcEditor()->setTextContent(vSrc);
    glslEditor->getFragSrcEditor()->setTextContent(fSrc);
}

void GlslFileHandler::handleGlslSave(const QString& path)
{
    if(path.isEmpty())
        return;

    // Save source to file
    QString vSrc = glslEditor->getVertexSource();
    QString fSrc = glslEditor->getFragmentSource();
    if(!IEShaderExport::exportShader(path, vSrc, fSrc))
        return;

    // Check if a shader exist to update
    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* shaderManager = scene->getManager<IEShaderManager>();
    uint64_t id = IEHash::Compute(path);
    auto* shader = shaderManager->value<IEShader>(id);
    if(!shader)
        return;

    shader->setVertexSrc(vSrc);
    shader->setFragmentSrc(fSrc);
    shader->build();
}

void GlslFileHandler::handleGlslSaveAs(const QString& path)
{
    if(path.isEmpty())
        return;

    if(askToSaveFile())
    {
        handleGlslSave(glslEditor->getCurrShaderPath());
    }

    QString vSrc = glslEditor->getVertexSource();
    QString fSrc = glslEditor->getFragmentSource();
    IEShaderExport::exportShader(path, vSrc, fSrc);

    glslEditor->getCurrShaderNameLabel()->setText("");
    glslEditor->getCurrShaderPathLabel()->setText("");

    glslEditor->openGlslFile(path);
}

bool GlslFileHandler::askToSaveFile()
{
    if(glslEditor->getCurrShaderPath().isEmpty())
        return false;

    int answer = QMessageBox::question(glslEditor,
                                       "Save Glsl File?",
                                       "Save before closing?",
                                       QMessageBox::No | QMessageBox::Yes);

    return (answer == QMessageBox::Yes);
}

QString GlslFileHandler::openSaveFileExplorer()
{
    QString path = QFileDialog::getSaveFileName(glslEditor,
                                                "Save Glsl File...",
                                                ".",
                                                "Glsl File (*.glsl)");
    return path;
}



