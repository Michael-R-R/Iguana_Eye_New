#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector2D>

#include "Serializable.h"

class ApplicationWindow;
class IETime;
class IEInput;
class IEScriptEngine;
class IEPhysicsEngine;
class IERenderEngine;
class IEScene;

class IEGame : public QOpenGLWidget, public Serializable
{
    Q_OBJECT

    std::unique_ptr<QSurfaceFormat> format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    std::unique_ptr<IETime> time;
    std::unique_ptr<IEInput> input;
    std::unique_ptr<IEScriptEngine> scriptEngine;
    std::unique_ptr<IEPhysicsEngine> physicsEngine;
    std::unique_ptr<IERenderEngine> renderEngine;
    std::unique_ptr<IEScene> scene;

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

    IETime& getIETime() { return *time; }
    IEInput& getIEInput() const { return *input; }
    IEScriptEngine& getIEScriptEngine() const { return *scriptEngine; }
    IEPhysicsEngine& getIEPhysicsEngine() const { return *physicsEngine; }
    IERenderEngine& getIERenderEngine() const { return *renderEngine; }
    IEScene& getIEScene() const { return *scene; }

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
