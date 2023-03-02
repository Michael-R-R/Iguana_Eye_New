#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDataStream>

#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "IEScene.h"

class ApplicationWindow;

// TODO test
#include "IETIslandGenerator.h"

class IEGame : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    IETime* time;
    IEInput* input;
    IERenderEngine* renderEngine;
    IEScene* scene;

    int viewportWidth;
    int viewportHeight;

    // TODO test
    IETIslandGenerator* testIsland = nullptr;

public:
    IEGame(QWidget* parent = nullptr);
    ~IEGame();

    IETime* getIETime() const { return time; }
    IEInput* getIEInput() const { return input; }
    IERenderEngine* getIERenderEngine() const { return renderEngine; }
    IEScene* getIEScene() const { return scene; }

    void init();
    void startup();
    void shutdown();

    int getViewportWidth() const { return viewportWidth; }
    int getViewportHeight() const { return viewportHeight; }

public slots:
    void onUpdateFrame();

private:
    void onRenderFrame();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

signals:
    void initialized();

public:
    friend QDataStream& operator<<(QDataStream& out, const IEGame& game)
    {
        out << *game.time << *game.input << *game.scene;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEGame& game)
    {
        in >> *game.time >> *game.input >> *game.scene;

        return in;
    }
};
