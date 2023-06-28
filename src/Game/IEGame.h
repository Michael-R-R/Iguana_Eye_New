#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include <QMap>

#include "Serializable.h"
#include "IEGameSystem.h"

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

    QVector<IEGameSystem*> systems;
    QHash<size_t, int> systemsIndex;

    IEGameState* state;

public:
    IEGame(QWidget* parent = nullptr);
    IEGame(const IEGame&) = delete;
    void operator=(const IEGame&) = delete;
    virtual ~IEGame();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

public:
    void startUp();
    void shutdown();
    void onSerialize();
    void onDeserialize();
    void changeState(IEGameState* val);
    bool doesSystemExist(size_t key) const;

    QOpenGLFunctions* getGlFunc() const { return glFunc; }
    QOpenGLExtraFunctions* getGlExtraFunc() const { return glExtraFunc; }

public slots:
    void onUpdateFrame();
    void onRenderFrame();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;

signals:
    void initialized();
    void stateChanged(const IEGameState* state);

public:
    template<class T>
    void appendSystem(IEGameSystem* system)
    {
        size_t key = typeid(T).hash_code();
        if(!system || doesSystemExist(key))
                return;

            const int index = systems.size();
            systems.append(system);
            systemsIndex.insert(key, index);
    }

    template<class T>
    T* getSystem() const
    {
        size_t key = typeid(T).hash_code();

        if(!doesSystemExist(key))
            return nullptr;

        return static_cast<T*>(systems[systemsIndex[key]]);
    }
};
