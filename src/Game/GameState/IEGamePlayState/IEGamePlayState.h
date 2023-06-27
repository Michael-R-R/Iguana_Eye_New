#pragma once

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IETime;
class IEPhysicsEngine;
class IERenderEngine;
class IEECS;

class IEGamePlayState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime* time;
    IEPhysicsEngine* physicsEngine;
    IERenderEngine* renderEngine;
    IEECS* ecs;

public:
    IEGamePlayState(IEGame& game);
    ~IEGamePlayState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;
};

