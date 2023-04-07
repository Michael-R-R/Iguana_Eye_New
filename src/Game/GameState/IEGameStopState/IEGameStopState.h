#pragma once

#include <memory>

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IERenderEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IERenderEngine* gRenderEngine;
    std::unique_ptr<ERenderEngine> eRenderEngine;
    std::unique_ptr<ECamera> eCamera;

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

