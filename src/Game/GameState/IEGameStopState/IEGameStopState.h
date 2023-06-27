#pragma once

#include "IEGameState.h"

class QOpenGLFunctions;
class QOpenGLExtraFunctions;
class IEGame;
class IETime;
class IEInput;
class IEECS;
class IERenderEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    QOpenGLFunctions* glFunc;
    QOpenGLExtraFunctions* glExtraFunc;
    IETime* time;
    IEInput* input;
    IEECS* ecs;
    IERenderEngine* gRenderEngine;

    ERenderEngine* eRenderEngine;
    ECamera* eCamera;

public:
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

public:
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

