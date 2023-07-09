#pragma once

#include "IEGameState.h"

class IETime;
class IEPhysicsEngine;
class IERenderEngine;
class IEECS;
class IEECSCameraSystem;

class IEGamePlayState : public IEGameState
{
    IETime* time;
    IEPhysicsEngine* pEngine;
    IERenderEngine* rEngine;
    IEECS* ecs;

    IEECSCameraSystem* cameraSystem;

public:
    IEGamePlayState(QObject* parent = nullptr);
    virtual ~IEGamePlayState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;
};

