#pragma once

#include <QSharedPointer>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IETime;
class IEInput;
class IERenderEngine;
class IEECSTransformSystem;
class ECSOnUpdateEvent;
class EPhysicsEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime& time;
    IEInput& input;
    IERenderEngine& gRenderEngine;
    IEECSTransformSystem* transformSystem;
    QSharedPointer<ECSOnUpdateEvent> ecsUpdateEvent;

    QSharedPointer<EPhysicsEngine> ePhysicsEngine;
    QSharedPointer<ERenderEngine> eRenderEngine;
    QSharedPointer<ECamera> eCamera;

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
};

