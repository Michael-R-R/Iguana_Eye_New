#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QDataStream>

#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "IEScene.h"

class Game : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    IETime* time;
    IEInput* input;
    IERenderEngine* renderEngine;
    IEScene* scene;

public:
    Game(QWidget* parent = nullptr);
    ~Game();

    void init();
    void startup();
    void shutdown();

    IETime* getIETime() const { return time; }
    IEInput* getIEInput() const { return input; }
    IERenderEngine* getIERenderEngine() const { return renderEngine; }
    IEScene* getIEScene() const { return scene; }

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
    friend QDataStream& operator<<(QDataStream& out, const Game& game)
    {
        out << *game.time << *game.input << *game.scene;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Game& game)
    {
        game.shutdown();
        game.init();

        in >> *game.time >> *game.input >> *game.scene;

        game.startup();

        return in;
    }
};
