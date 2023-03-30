#pragma once

#include "IEGameState.h"

class IETime;
class IEPhysicsEngine;
class IERenderEngine;
class IEScene;
class QOpenGLFunctions;
class QOpenGLExtraFunctions;

class IEGamePlayState : public IEGameState
{
    IETime& time;
    IEPhysicsEngine& physicsEngine;
    IERenderEngine& renderEngine;
    IEScene& scene;
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;

public:
    IEGamePlayState(IEGame& game);
    ~IEGamePlayState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame(IEGame& game) override;
    void onRenderFrame(IEGame& game) override;
};

