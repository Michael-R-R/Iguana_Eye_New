#pragma once

#include <memory>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IETime;
class IERenderEngine;
class EDefaultCamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime& time;
    IERenderEngine& renderEngine;
    std::unique_ptr<EDefaultCamera> camera;

public:
    IEGameStopState(IEGame& game);
    ~IEGameStopState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
};

