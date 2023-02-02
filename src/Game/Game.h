#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "IETime.h"
#include "IEInput.h"
#include "IEScene.h"

class Game : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    IETime* time;
    IEInput* input;
    IEScene* scene;

public:
    Game(QWidget* parent = nullptr);
    ~Game();

    void startup();
    void shutdown();

    IETime* getTime() const { return time; }
    IEInput* getInput() const { return input; }
    IEScene* getScene() const { return scene; }

public slots:
    void onUpdateFrame();
    void onRenderFrame();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;

signals:
    void initialized();
};

