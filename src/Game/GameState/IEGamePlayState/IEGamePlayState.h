#pragma once

#include <memory>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEPhysicsEngine;
class IERenderEngine;
class IEECSScriptSystem;
class IEECSRigidbody3DSystem;
class IEECSTransformSystem;
class IEECSCameraSystem;
class ECSOnUpdateEvent;

class IEGamePlayState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IEPhysicsEngine* physicsEngine;
    IERenderEngine* renderEngine;
    IEECSScriptSystem* scriptSystem;
    IEECSRigidbody3DSystem* rigidbody3dSystem;
    IEECSTransformSystem* transformSystem;
    IEECSCameraSystem* cameraSystem;
    std::unique_ptr<ECSOnUpdateEvent> ecsUpdateEvent;

public:
    IEGamePlayState(IEGame& game);
    ~IEGamePlayState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;
};

