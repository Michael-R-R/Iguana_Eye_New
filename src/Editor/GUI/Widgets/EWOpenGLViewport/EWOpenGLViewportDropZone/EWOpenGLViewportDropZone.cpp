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
#include "IEHash.h"
#include "IEObjImporter.h"
#include <QFileInfo>

EWOpenGLViewportDropZone::EWOpenGLViewportDropZone(QWidget* parent) :
    QWidget(parent)
{

}

void EWOpenGLViewportDropZone::startup(const AppStartEvent& event)
{
    auto host = event.getGame();
    host->setAcceptDrops(true);
    host->installEventFilter(this);
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
    auto& meshManager = IEScene::instance().getMeshManager();
    auto& materialManager = IEScene::instance().getMaterialManager();
    auto& shaderManager = IEScene::instance().getShaderManager();
    auto& renderableManager = IEScene::instance().getRenderableManager();

    const unsigned long long meshId = IEHash::Compute(path);
    const unsigned long long materialId = materialManager.getDefaultId();
    const unsigned long long shaderId = shaderManager.getDefaultId();

    if(!meshManager.doesExist(meshId))
    {
        auto mesh = QSharedPointer<IEMesh>::create(path);
        if(!IEObjImporter::importMesh(path, *mesh))
            return;

        meshManager.add(meshId, mesh);
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

    // TODO set renderable id

    if(renderableManager.doesExist(meshId, materialId, shaderId))
    {
        // add instance renderable
        renderableSystem->addShown(rIndex);
    }
    else
    {
        // create new renderable
    }
}
