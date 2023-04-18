#pragma once

#include <QSharedPointer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "Serializable.h"

class ApplicationWindow;
class IERenderEngine;
class IEPhysicsEngine;
class IEScene;
class IEECS;
class IEInput;
class IEScriptEngine;
class IETime;
class IEGameState;

class IEGame : public QOpenGLWidget, public Serializable
{
    Q_OBJECT

    QSurfaceFormat format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    IERenderEngine* renderEngine;
    IEPhysicsEngine* physicsEngine;
    IEScene* scene;
    QSharedPointer<IEECS> ecs;
    QSharedPointer<IEInput> input;
    QSharedPointer<IEScriptEngine> scriptEngine;
    QSharedPointer<IETime> time;
    IEGameState* state;

public:
    IEGame(QWidget* parent = nullptr);
    IEGame(const IEGame&) = delete;
    void operator=(const IEGame&) = delete;
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
    void changeState(IEGameState* val);

    QOpenGLFunctions* getGlFunc() const { return glFunc; }
    QOpenGLExtraFunctions* getGlExtraFunc() const { return glExtraFunc; }
    IERenderEngine* getRenderEngine() const { return renderEngine; }
    IEPhysicsEngine* getPhysicsEngine() const { return physicsEngine; }
    IEScene* getScene() const { return scene; }
    IEECS& getECS() const { return *ecs; }
    IEInput& getInput() const { return *input; }
    IEScriptEngine& getScriptEngine() const { return *scriptEngine; }
    IETime& getTime() const { return *time; }

public slots:
    void onUpdateFrame();
    void onRenderFrame();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

signals:
    void initialized();
    void stateChanged(const IEGameState* state);
};
