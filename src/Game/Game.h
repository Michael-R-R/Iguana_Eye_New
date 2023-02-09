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

        game.time = new IETime(0, 0, &game);
        game.input = new IEInput(&game, &game);
        game.scene = new IEScene(&game);

        in >> *game.time >> *game.input >> *game.scene;

        game.startup();

        return in;
    }
};
