#include "OpenGLFileHandler.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"
#include "IEECSRenderableSystem.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEEntity.h"
#include "IEFile.h"
#include "IEHash.h"
#include "IEMeshImport.h"
#include "IERenderableImport.h"
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
    auto* scene = game->getSystem<IEScene>();
    auto* meManager = scene->getSystem<IEMeshManager>();
    auto* maManager = scene->getSystem<IEMaterialManager>();
    auto* sManager = scene->getSystem<IEShaderManager>();
    auto* rManager = scene->getSystem<IERenderableManager>();
    auto* ecs = scene->getSystem<IEECS>();
    game->makeCurrent();

    uint64_t sID = sManager->getDefaultID();

    // --- Create or get mesh --- //
    uint64_t meID = IEHash::Compute(IEMeshImport::convertMeshPath(path));
    uint64_t maID = IEHash::Compute(IEMeshImport::convertMaterialPath(path));
    uint64_t rID = IEHash::Compute(IERenderableImport::convertRenderablePath(path));

    bool isMesh = meManager->doesExist(meID);
    bool isMaterial = maManager->doesExist(meID);

    auto* renderable = rManager->value<IERenderable>(rID);
    if(renderable)
    {
        if(renderable->getShaderID() != sID)
        {
            // TODO implement
        }
    }

    IEEntity entity = ecs->create();
    int rIndex = ecs->attachComponent<IEECSRenderableSystem>(entity);
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
