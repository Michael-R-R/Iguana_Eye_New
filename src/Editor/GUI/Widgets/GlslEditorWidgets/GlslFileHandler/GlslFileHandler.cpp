#include "GlslFileHandler.h"
#include "EWGlslEditor.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEGlslImporter.h"
#include "IEGlslExporter.h"
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
    IEGlslExporter::exportGlsl(path, vSrc, fSrc);

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
    IEGlslImporter::importGlsl(path, vSrc, fSrc);

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
    if(!IEGlslExporter::exportGlsl(path, vSrc, fSrc))
        return;

    // Check if a shader exist to update
    auto& shaderManager = IEScene::instance().getShaderManager();
    unsigned long long id = IEHash::Compute(path);
    auto shader = shaderManager.value(id);
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
    IEGlslExporter::exportGlsl(path, vSrc, fSrc);

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



