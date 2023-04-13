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
#include "IEEntity.h"
#include "IEFile.h"
#include "IEHash.h"
#include "IEObjImporter.h"
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
    auto& scene = game->getScene();
    auto& meshManager = scene.getMeshManager();
    auto& materialManager = scene.getMaterialManager();
    auto& shaderManager = scene.getShaderManager();
    auto& renderableManager = scene.getRenderableManager();

    const unsigned long long meshId = IEHash::Compute(path);
    const unsigned long long materialId = materialManager.getDefaultId();
    const unsigned long long shaderId = shaderManager.getDefaultId();

    QSharedPointer<IEMesh> mesh = nullptr;
    if(!meshManager.doesExist(meshId))
    {
        mesh = QSharedPointer<IEMesh>::create(path);
        if(!IEObjImporter::importMesh(path, *mesh))
            return;

        meshManager.add(meshId, mesh);
    }
    else
    {
        mesh = meshManager.value(meshId);
    }

    // --- Create entity and attach components --- //
    auto& ecs = game->getECS();
    auto* meshSystem = ecs.getComponent<IEECSMeshSystem>();
    auto* materialSystem = ecs.getComponent<IEECSMaterialSystem>();
    auto* shaderSystem = ecs.getComponent<IEECSShaderSystem>();
    auto* renderableSystem = ecs.getComponent<IEECSRenderableSystem>();

    IEEntity entity = ecs.create();
    const int meIndex = ecs.attachComponent<IEECSMeshSystem>(entity);
    const int maIndex = ecs.attachComponent<IEECSMaterialSystem>(entity);
    const int sIndex = ecs.attachComponent<IEECSShaderSystem>(entity);
    const int rIndex = ecs.attachComponent<IEECSRenderableSystem>(entity);

    meshSystem->setMeshId(meIndex, meshId);
    materialSystem->setMaterialId(maIndex, materialId);
    shaderSystem->setShaderId(sIndex, shaderId);

    // --- Create renderable or create instance --- //
    QString rPath = QString("./resources/renderables/%1/%2/%3/r.ierend").arg(QString::number(meshId),
                                                                             QString::number(materialId),
                                                                             QString::number(shaderId));
    unsigned long long rID = IEHash::Compute(rPath);

    if(!renderableManager.doesExist(rID))
    {
        auto rType = (mesh->getIndices().size() > 0) ? IERenderable::RenderMode::I_Index : IERenderable::RenderMode::I_Vertex;

        // create new renderable
        QSharedPointer<IERenderable> renderable = QSharedPointer<IERenderable>::create(rPath, meshId, materialId, shaderId);
        renderable->setDrawType(GL_TRIANGLES);
        renderable->setRenderMode(rType);
        renderable->addIndexBuffer(QSharedPointer<IEIndexBuffer>::create(mesh->getIndices()));
        renderable->addVec3Buffer("aPos", QSharedPointer<IEVertexBuffer<QVector3D>>::create(mesh->getPosVertices(), 12, 3, 0, 0, 0));
        renderable->addMat4Buffer("aModel", QSharedPointer<IEVertexBuffer<QMatrix4x4>>::create(QVector<QMatrix4x4>(), 68, 4, 68, 4, 16));

        auto shader = shaderManager.value(shaderId);
        renderable->build(*shader);

        renderableManager.add(rID, renderable);

        renderableSystem->setRenderableId(rIndex, rID);
        renderableSystem->addShown(rIndex);
    }
    else
    {
        renderableSystem->setRenderableId(rIndex, rID);
        renderableSystem->addShown(rIndex);
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
