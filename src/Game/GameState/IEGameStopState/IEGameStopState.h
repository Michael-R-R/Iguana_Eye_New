#pragma once

#include <QSharedPointer>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IEECSTransformSystem;
class ECSOnUpdateEvent;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IEECSTransformSystem* transformSystem;
    QSharedPointer<ECSOnUpdateEvent> ecsUpdateEvent;

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
    void serializeGameStates();
    void deserializeGameStates();
};

