#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QPair>

#include "Serializable.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"

class ApplicationWindow;
class IETime;

class IEGame : public QOpenGLWidget, public Serializable
{
    Q_OBJECT

    QSurfaceFormat* format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    std::unique_ptr<IETime> time;
    IEInput* input;
    IEScriptEngine* scriptEngine;
    IERenderEngine* renderEngine;
    IEScene* scene;

    int viewportWidth;
    int viewportHeight;

public:
    IEGame(QWidget* parent = nullptr);
    ~IEGame();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

public:
    void init();
    void startup();
    void shutdown();

    IETime& getIETime() { return *time; }
    IEInput* getIEInput() const { return input; }
    IEScriptEngine* getIEScriptEngine() const { return scriptEngine; }
    IERenderEngine* getIERenderEngine() const { return renderEngine; }
    IEScene* getIEScene() const { return scene; }
    QPair<int, int> viewportSize() { return QPair<int, int>(viewportWidth, viewportHeight); }

public slots:
    void onUpdateFrame();

private:
    void onRenderFrame();

signals:
    void initialized();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
