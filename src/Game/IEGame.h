#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "Serializable.h"

class ApplicationWindow;
class IEScriptEngine;
class IERenderEngine;
class IEGameState;

class IEGame : public QOpenGLWidget, public Serializable
{
    Q_OBJECT

    QSurfaceFormat format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    std::unique_ptr<IEScriptEngine> scriptEngine;
    std::unique_ptr<IERenderEngine> renderEngine;

    std::unique_ptr<IEGameState> state;

public:
    IEGame(QWidget* parent = nullptr);
    ~IEGame();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

public:
    void startup();
    void shutdown();
    void initalize();
    void reset();
    void changeState(std::unique_ptr<IEGameState> val);

    IEScriptEngine& getIEScriptEngine() const { return *scriptEngine; }
    IERenderEngine& getIERenderEngine() const { return *renderEngine; }
    QOpenGLFunctions* getGlFunc() { return glFunc; }
    QOpenGLExtraFunctions* getGlExtraFunc() { return glExtraFunc; }

public slots:
    void onUpdateFrame();
    void onRenderFrame();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

signals:
    void initialized();
};
