#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDataStream>

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

    IETime* getIETime() const { return time; }
    IEInput* getIEInput() const { return input; }
    IEScene* getIEScene() const { return scene; }

    void setIETime(IETime* val) { time = val; }
    void setIEInput(IEInput* val) { input = val; }
    void setIEScene(IEScene* val) { scene = val; }

public slots:
    void onUpdateFrame();
    void onRenderFrame();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;

signals:
    void initialized();
};

QDataStream& operator<<(QDataStream& out, const Game& game);
QDataStream& operator>>(QDataStream& in, Game& game);
