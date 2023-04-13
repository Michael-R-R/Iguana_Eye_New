#pragma once

#include <QSharedPointer>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IETime;
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
    IETime& time;
    IEPhysicsEngine& physicsEngine;
    IERenderEngine& gRenderEngine;
    IEECSScriptSystem* scriptSystem;
    IEECSRigidbody3DSystem* rigidbody3dSystem;
    IEECSTransformSystem* transformSystem;
    IEECSCameraSystem* cameraSystem;
    QSharedPointer<ECSOnUpdateEvent> ecsUpdateEvent;

public:
    IEGamePlayState(IEGame& game);
    ~IEGamePlayState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;
};

