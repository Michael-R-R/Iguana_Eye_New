#include "EWOpenGLViewportDropZone.h"
#include <QFileInfo>

EWOpenGLViewportDropZone::EWOpenGLViewportDropZone(QWidget* parent) :
    QWidget(parent)
{

}

void EWOpenGLViewportDropZone::installEventFilterOnHost(QOpenGLWidget* host)
{
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

void EWOpenGLViewportDropZone::dragMoveEvent(QDragMoveEvent*)
{
    return;
}

void EWOpenGLViewportDropZone::dragLeaveEvent(QDragLeaveEvent*)
{
    return;
}

void EWOpenGLViewportDropZone::dropEvent(QDropEvent* event)
{
    const QMimeData* data = event->mimeData();
    if(!data->hasUrls())
        return;

    foreach(auto url, data->urls())
    {
        qDebug() << url.toLocalFile();
    }
}

void EWOpenGLViewportDropZone::checkEvent(QEvent* event)
{
    switch(event->type())
    {
    case QEvent::DragEnter: { dragEnterEvent(static_cast<QDragEnterEvent*>(event)); break; }
    case QEvent::DragMove: { dragMoveEvent(static_cast<QDragMoveEvent*>(event)); break; }
    case QEvent::DragLeave: { dragLeaveEvent(static_cast<QDragLeaveEvent*>(event)); break; }
    case QEvent::Drop: { dropEvent(static_cast<QDropEvent*>(event)); break; }
    default: { break; }
    }
}
