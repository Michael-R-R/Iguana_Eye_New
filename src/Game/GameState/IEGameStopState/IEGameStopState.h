#pragma once

#include <memory>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IETime;
class IEInput;
class IERenderEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime* time;
    IEInput* input;
    IERenderEngine* gRenderEngine;
    std::unique_ptr<ERenderEngine> eRenderEngine;
    std::unique_ptr<ECamera> eCamera;

public:
    IEGameStopState();
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

