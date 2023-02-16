#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "EWOpenGLViewportTime.h"
#include "EWOpenGLViewportInput.h"
#include "IERenderEngine.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"

class EWOpenGLViewport : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    EWOpenGLViewportTime* time;
    EWOpenGLViewportInput* input;

    IERenderEngine* renderEngine;

    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;

public:
    EWOpenGLViewport(const QString title, QWidget* parent = nullptr);
    ~EWOpenGLViewport();

    void startup();
    void shutdown();

    void addRenderableCopy(const IEMesh* mesh, const IEMaterial* material,
                           const IEShader* shader, const IERenderable* renderable);

    virtual void onUpdateFrame();

protected:
    virtual void onRenderFrame();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
    void initialized();
};

