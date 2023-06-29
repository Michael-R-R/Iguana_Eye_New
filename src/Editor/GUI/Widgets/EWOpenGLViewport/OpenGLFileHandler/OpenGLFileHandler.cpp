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
    auto* scene = game->getSystem<IEScene>();
    auto* meManager = scene->getManager<IEMeshManager>();
    auto* maMaterial = scene->getManager<IEMaterialManager>();
    auto* sManager = scene->getManager<IEShaderManager>();
    auto* rManager = scene->getManager<IERenderableManager>();

    const uint64_t meshId = IEHash::Compute(path);
    const uint64_t materialId = maMaterial->getDefaultId();
    const uint64_t shaderId = sManager->getDefaultId();

    IEMesh* mesh = nullptr;
    if(!meManager->doesExist(meshId))
    {
        mesh = new IEMesh(path, meManager);
        if(!IEMeshImport::importMesh(path, *mesh))
            return;

        if(!meManager->add(meshId, mesh))
        {
            delete mesh;
            return;
        }
    }
    else
    {
        mesh = meManager->value<IEMesh>(meshId);
    }

    // --- Create entity and attach components --- //
    auto* ecs = game->getSystem<IEECS>();
    auto* meSystem = ecs->getComponent<IEECSMeshSystem>();
    auto* maSystem = ecs->getComponent<IEECSMaterialSystem>();
    auto* sSystem = ecs->getComponent<IEECSShaderSystem>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();

    IEEntity entity = ecs->create();
    const int meIndex = ecs->attachComponent<IEECSMeshSystem>(entity);
    const int maIndex = ecs->attachComponent<IEECSMaterialSystem>(entity);
    const int sIndex = ecs->attachComponent<IEECSShaderSystem>(entity);
    const int rIndex = ecs->attachComponent<IEECSRenderableSystem>(entity);

    meSystem->setResourceId(meIndex, meshId);
    maSystem->setResourceId(maIndex, materialId);
    sSystem->setResourceId(sIndex, shaderId);

    // --- Create renderable or create instance --- //
    QString rPath = QString("./resources/renderables/%1/%2/%3/r.ierend").arg(QString::number(meshId),
                                                                             QString::number(materialId),
                                                                             QString::number(shaderId));
    const uint64_t rID = IEHash::Compute(rPath);

    if(!rManager->doesExist(rID))
    {
        auto rType = (mesh->getIndices().size() > 0) ? IERenderable::RenderMode::I_Index : IERenderable::RenderMode::I_Vertex;

        // create new renderable
        auto* renderable = new IERenderable(rPath, meshId, materialId, shaderId, rManager);
        renderable->setDrawType(GL_TRIANGLES);
        renderable->setRenderMode(rType);
        renderable->addIndexBuffer(new IEIndexBuffer(mesh->getIndices(), renderable));
        renderable->addVec3Buffer("aPos", new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0, renderable));
        renderable->addMat4Buffer("aModel", new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 68, 4, 68, 4, 16, renderable));

        auto shader = sManager->value<IEShader>(shaderId);
        renderable->build(*shader);

        if(!rManager->add(rID, renderable))
        {
            delete renderable;
            return;
        }

        rSystem->setResourceId(rIndex, rID);
        rSystem->addShown(rIndex);
    }
    else
    {
        rSystem->setResourceId(rIndex, rID);
        rSystem->addShown(rIndex);
    }
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
