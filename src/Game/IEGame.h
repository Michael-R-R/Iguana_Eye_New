#pragma once

#include <QDataStream>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "IETime.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"

class ApplicationWindow;

class IEGame : public QOpenGLWidget
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    IETime* time;
    IEInput* input;
    IEScriptEngine* scriptEngine;
    IERenderEngine* renderEngine;
    IEScene* scene;

    int viewportWidth;
    int viewportHeight;

public:
    IEGame(QWidget* parent = nullptr);
    ~IEGame();

    IETime* getIETime() const { return time; }
    IEInput* getIEInput() const { return input; }
    IEScriptEngine* getIEScriptEngine() const { return scriptEngine; }
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
