#pragma once

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QSharedPointer>

class QOpenGLWidget;
class OpenGLFileDropHandler;

class EWOpenGLViewportDropZone : public QWidget
{
    Q_OBJECT

    QOpenGLWidget* glWidget;
    QSharedPointer<OpenGLFileDropHandler> fileHandler;

public:
    EWOpenGLViewportDropZone(QWidget* parent = nullptr);
    ~EWOpenGLViewportDropZone() {}

    void startup();
    void shutdown();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void checkEvent(QEvent* event);
};

