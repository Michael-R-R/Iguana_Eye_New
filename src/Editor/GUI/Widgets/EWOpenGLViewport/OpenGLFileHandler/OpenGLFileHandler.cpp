#include "OpenGLFileHandler.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEEntity.h"
#include "IEFile.h"
#include "IEHash.h"
#include "IEMeshImport.h"
#include "Editor.h"
#include "EGUI.h"
#include "EWindowManager.h"
#include "EGlslEditorWindow.h"

OpenGLFileHandler::OpenGLFileHandler()
{

}

OpenGLFileHandler::~OpenGLFileHandler()
{

}

void OpenGLFileHandler::handle(const QString& path)
{
    if(path.isEmpty())
        return;

    QString extension = IEFile::extractExtension(path);

    if(extension == ".obj")
        handleObjFile(path);
    else if(extension == ".glsl")
        handleGlslFile(path);
}

void OpenGLFileHandler::handleObjFile(const QString& path)
{
    auto& application = ApplicationWindow::instance();
    auto* game = application.getGame();
    game->makeCurrent();

    // --- Create or get mesh --- //
    // TODO implement
}

void OpenGLFileHandler::handleGlslFile(const QString& path)
{
    auto& application = ApplicationWindow::instance();
    auto editor = application.getEditor();
    auto* ui = editor->getUi();
    auto* windows = ui->getWindowManager();
    auto* glslWindow = windows->findWindow<EGlslEditorWindow>();
    if(!glslWindow)
        return;

    auto* glslEditor = glslWindow->getGlslEditorWidget();
    glslEditor->openGlslFile(path);

    glslWindow->show();
}
