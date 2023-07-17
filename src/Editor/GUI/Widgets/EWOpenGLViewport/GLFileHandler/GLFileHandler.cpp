#include "GLFileHandler.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "IEECSRenderableSystem.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IEInstIndexRenderable.h"
#include "IEEntity.h"
#include "IEFile.h"
#include "IEHash.h"
#include "IEMeshImport.h"
#include "IERenderableImport.h"
#include "Editor.h"
#include "EGUI.h"
#include "EWindowManager.h"
#include "EGlslEditorWindow.h"

GLFileHandler::GLFileHandler()
{

}

GLFileHandler::~GLFileHandler()
{

}

void GLFileHandler::handle(const QString& path)
{
    if(path.isEmpty())
        return;

    QString extension = IEFile::extractExtension(path);

    if(extension == ".obj")
        handleObjFile(path);
    else if(extension == ".glsl")
        handleGlslFile(path);
}

void GLFileHandler::handleObjFile(const QString& path)
{
    auto& application = ApplicationWindow::instance();
    auto* game = application.getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* maManager = scene->getSystem<IEMaterialManager>();
    auto* sManager = scene->getSystem<IEShaderManager>();
    auto* rManager = scene->getSystem<IERenderableManager>();
    auto* ecs = scene->getSystem<IEECS>();
    game->makeCurrent();

    uint64_t sID = sManager->getDefaultID();
    IEShader* shader = sManager->value<IEShader>(sID);

    // --- Get renderable --- //
    uint64_t maID = IEHash::Compute(IEMeshImport::convertMaterialPath(path));
    uint64_t rID = IEHash::Compute(IERenderableImport::convertRenderablePath(path));

    if(!rManager->doesExist(rID))
    {
        IEMesh mesh;
        IEMaterial* material = nullptr;
        IEInstIndexRenderable* renderable = nullptr;

        if(!maManager->doesExist(maID))
        {
            material = new IEMaterial(maManager);
            IEMeshImport::importPath(path, mesh, *material);
        }
        else
        {
            material = maManager->value<IEMaterial>(maID);
        }

        renderable = new IEInstIndexRenderable(rManager);
        IERenderableImport::importPath(path, *renderable, mesh, maID, sID);

        const int nodeCount = renderable->getNodes().size();
        for(int i = 0; i < nodeCount; i++)
        {
            auto* ibo = renderable->getInstIndexNode(i)->IBO;
            ibo->setValues(mesh.getNode(i)->indices);
            renderable->addBuffer(i, "aModel", IEBufferType::Mat4, 64, 16, 4);
            renderable->build(i, *shader);
        }

        maManager->add(maID, material);
        rManager->add(rID, renderable);
    }

    // --- Create entity --- //
    auto* tSystem = ecs->getComponent<IEECSTransformSystem>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();

    IEEntity entity = ecs->create();
    int rIndex = ecs->attachComponent<IEECSRenderableSystem>(entity);
    int tIndex = tSystem->lookUpIndex(entity);

    rSystem->setResourceId(rIndex, rID);
    rSystem->showInstance(rIndex);

    tSystem->setPosition(tIndex, glm::vec3(0.0f));
}

void GLFileHandler::handleGlslFile(const QString& path)
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
