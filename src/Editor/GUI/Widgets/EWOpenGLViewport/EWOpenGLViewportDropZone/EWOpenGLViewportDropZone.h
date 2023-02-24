#pragma once

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QOpenGLWidget>

class EWOpenGLViewportDropZone : public QWidget
{
    Q_OBJECT

public:
    EWOpenGLViewportDropZone(QWidget* parent = nullptr);
    ~EWOpenGLViewportDropZone() {}

    void installEventFilterOnHost(QOpenGLWidget* host);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void checkEvent(QEvent* event);
};

