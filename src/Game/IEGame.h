#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include <QMap>

#include "IESerializable.h"
#include "IESystem.h"

class IEGameState;

class IEGame : public QOpenGLWidget, public IESerializable
{
    Q_OBJECT

    QSurfaceFormat format;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

    QVector<IESystem*> systems;
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
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;

signals:
    void initialized();
    void stateChanged(const IEGameState* state);

public:
    template<class T>
    bool appendSystem(IESystem* system)
    {
        size_t key = typeid(T).hash_code();
        if(!system || doesSystemExist(key))
                return false;

        const int index = systems.size();
        systems.append(system);
        systemsIndex.insert(key, index);

        return true;
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
