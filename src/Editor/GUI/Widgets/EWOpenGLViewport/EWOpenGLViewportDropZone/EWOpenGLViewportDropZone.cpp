#include "EWOpenGLViewportDropZone.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "OpenGLFileDropHandler.h"
#include <QFileInfo>
#include <QOpenGLWidget>

EWOpenGLViewportDropZone::EWOpenGLViewportDropZone(QWidget* parent) :
    QWidget(parent),
    glWidget(nullptr),
    fileHandler(QSharedPointer<OpenGLFileDropHandler>::create())
{

}

void EWOpenGLViewportDropZone::startup()
{
    auto& application = ApplicationWindow::instance();
    auto game = application.getGame();

    glWidget = &(*game);
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

    for(auto& i : data->urls())
    {
        if(QFileInfo(i.toLocalFile()).isDir())
            return;
    }

    event->acceptProposedAction();
}

void EWOpenGLViewportDropZone::dropEvent(QDropEvent* event)
{
    const QMimeData* data = event->mimeData();
    if(!data->hasUrls())
        return;

    foreach(auto url, data->urls())
    {
        fileHandler->handle(glWidget, url.toLocalFile());
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
