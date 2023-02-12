#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "GLTime.h"
#include "GLInput.h"
#include "IERenderEngine.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"

class GLViewport : public QOpenGLWidget
{
    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    GLTime* time;
    GLInput* input;

    IERenderEngine* renderEngine;

    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;

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

