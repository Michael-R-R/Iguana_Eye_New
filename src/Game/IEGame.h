#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "Serializable.h"

class ApplicationWindow;
class IEGameState;

class IEGame : public QOpenGLWidget, public Serializable
{
    Q_OBJECT

    QSurfaceFormat format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    QSharedPointer<IEGameState> state;

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
    void changeState(QSharedPointer<IEGameState> val);

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
