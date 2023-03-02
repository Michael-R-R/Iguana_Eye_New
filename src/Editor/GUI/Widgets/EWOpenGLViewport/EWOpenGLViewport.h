#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "EWOpenGLViewportTime.h"
#include "EWOpenGLViewportInput.h"

class EWOpenGLViewport : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    EWOpenGLViewportTime* time;
    EWOpenGLViewportInput* input;

public:
    EWOpenGLViewport(const QString title, QWidget* parent = nullptr);
    ~EWOpenGLViewport();

    void startup();
    void shutdown();

    virtual void onUpdateFrame();

protected:
    virtual void onRenderFrame();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
    void initialized();
};

