#include "EWOpenGLViewportDropZone.h"
#include "AppStartEvent.h"
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
#include "IESerialize.h"
#include "IEHash.h"
#include "IEObjImporter.h"
#include <QFileInfo>
#include <QOpenGLWidget>

EWOpenGLViewportDropZone::EWOpenGLViewportDropZone(QWidget* parent) :
    QWidget(parent),
    glWidget(nullptr)
{

}

void EWOpenGLViewportDropZone::startup(const AppStartEvent& event)
{
    glWidget = event.getGame();
    glWidget->setAcceptDrops(true);
    glWidget->installEventFilter(this);
}

bool EWOpenGLViewportDropZone::eventFilter(QObject* watched, QEvent* event)
{
    checkEvent(event);

    return QObject::eventFilter(watched, event);
}

void EWOpenGLViewportDropZone::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* data = event->mimeData();
    if(!data->hasUrls())
        return;

    if(data->urls().size() > 1)
        return;

    QString path = data->urls().at(0).toLocalFile();
    if(QFileInfo(path).isDir())
        return;

    event->acceptProposedAction();
}

void EWOpenGLViewportDropZone::dropEvent(QDropEvent* event)
{
    const QMimeData* data = event->mimeData();
    if(!data->hasUrls())
        return;

    foreach(auto url, data->urls())
    {
        QString path = url.toLocalFile();
        QString ext = IEFile::extractExtension(url.toLocalFile());
        if(ext == ".obj")
            handleObjFile(path);
    }
}

void EWOpenGLViewportDropZone::checkEvent(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::DragEnter: { dragEnterEvent(static_cast<QDragEnterEvent*>(event)); break; }
    case QEvent::Drop: { dropEvent(static_cast<QDropEvent*>(event)); break; }
    default: { break; }
    }
}

void EWOpenGLViewportDropZone::handleObjFile(const QString& path)
{
    glWidget->makeCurrent();

    auto& meshManager = IEScene::instance().getMeshManager();
    auto& materialManager = IEScene::instance().getMaterialManager();
    auto& shaderManager = IEScene::instance().getShaderManager();
    auto& renderableManager = IEScene::instance().getRenderableManager();

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

    auto& ecs = IEECS::instance();
    auto* meshSystem = ecs.getComponent<IEECSMeshSystem>("Mesh");
    auto* materialSystem = ecs.getComponent<IEECSMaterialSystem>("Material");
    auto* shaderSystem = ecs.getComponent<IEECSShaderSystem>("Shader");
    auto* renderableSystem = ecs.getComponent<IEECSRenderableSystem>("Renderable");

    // Create entity and attach components
    IEEntity entity = ecs.create();
    const int meIndex = ecs.attachComponent(entity, "Mesh");
    const int maIndex = ecs.attachComponent(entity, "Material");
    const int sIndex = ecs.attachComponent(entity, "Shader");
    const int rIndex = ecs.attachComponent(entity, "Renderable");

    meshSystem->setMeshId(meIndex, meshId);
    materialSystem->setMaterialId(maIndex, materialId);
    shaderSystem->setShaderId(sIndex, shaderId);

    QString rPath = QString("./resources/renderables/%1/%2/%3/r.ierend").arg(QString::number(meshId),
                                                                             QString::number(materialId),
                                                                             QString::number(shaderId));

    unsigned long long rID = IEHash::Compute(rPath);

    if(!renderableManager.doesExist(meshId, materialId, shaderId))
    {
        auto rType = (mesh->getIndices().size() > 0) ? IERenderable::RenderMode::I_Index : IERenderable::RenderMode::I_Vertex;

        // create new renderable
        QSharedPointer<IERenderable> renderable = QSharedPointer<IERenderable>::create(rPath, meshId, materialId, shaderId);
        renderable->setDrawType(GL_TRIANGLES);
        renderable->setRenderMode(rType);
        renderable->addIndexBuffer(QSharedPointer<IEIndexBuffer>::create(mesh->getIndices()));
        renderable->addVec3Buffer("aPos", QSharedPointer<IEVertexBuffer<QVector3D>>::create(mesh->getPosVertices(), 12, 3, 0, 0, 0));
        renderable->addMat4Buffer("aModel", QSharedPointer<IEVertexBuffer<QGenericMatrix<4,4,float>>>::create(QVector<QGenericMatrix<4,4,float>>(), 64, 4, 64, 4, 16));

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
