#pragma once

#include <QSharedPointer>

#include "IEGameState.h"
#include "ECSOnUpdateEvent.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IETime;
class IEInput;
class IERenderEngine;
class EPhysicsEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime& time;
    IEInput& input;
    IERenderEngine* gRenderEngine;
    ECSOnUpdateEvent ecsUpdateEvent;

    EPhysicsEngine* ePhysicsEngine;
    ERenderEngine* eRenderEngine;
    ECamera* eCamera;

public:
    IEGameStopState(IEGame& game);
    ~IEGameStopState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;

private:
    void serializeGameStates(IEGame& game);
    void deserializeGameStates(IEGame& game);

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

