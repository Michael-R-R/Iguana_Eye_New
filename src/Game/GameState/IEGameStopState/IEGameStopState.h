#pragma once

#include <memory>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IETime;
class IERenderEngine;
class IEECSTransformSystem;
class IEECSCameraSystem;
class ECSOnUpdateEvent;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime& time;
    IERenderEngine& renderEngine;
    IEECSTransformSystem* transformSystem;
    IEECSCameraSystem* cameraSystem;
    std::unique_ptr<ECSOnUpdateEvent> ecsUpdateEvent;

public:
    IEGameStopState(IEGame& game);
    ~IEGameStopState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
};

