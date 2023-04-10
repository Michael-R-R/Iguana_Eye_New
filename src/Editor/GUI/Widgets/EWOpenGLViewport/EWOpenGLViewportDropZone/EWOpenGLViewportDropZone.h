#pragma once

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class AppStartEvent;
class QOpenGLWidget;

class EWOpenGLViewportDropZone : public QWidget
{
    Q_OBJECT

    QOpenGLWidget* glWidget;

public:
    EWOpenGLViewportDropZone(QWidget* parent = nullptr);
    ~EWOpenGLViewportDropZone() {}

    void startup(const AppStartEvent& event);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void checkEvent(QEvent* event);
    void handleObjFile(const QString& path);
};

