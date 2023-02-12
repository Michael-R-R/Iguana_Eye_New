#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "GLTime.h"
#include "GLInput.h"

class GLViewport : public QOpenGLWidget
{
    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    GLTime* time;
    GLInput* input;

public:
    GLViewport(const QString title, QWidget* parent = nullptr);
    ~GLViewport();

    void startup();
    void shutdown();

    virtual void onUpdateFrame();

protected:
    virtual void onRenderFrame();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

