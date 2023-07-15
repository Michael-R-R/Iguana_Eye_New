#pragma once

#include "IEGameState.h"

class IEGame;
class IETime;
class IEInput;
class IEECS;
class IERenderEngine;
class ERenderEngine;
class ECamera;

class IEGameStopState : public IEGameState
{
    IETime* time;
    IEInput* input;
    IEECS* ecs;
    IERenderEngine* grEngine;

    ERenderEngine* erEngine;
    ECamera* eCamera;

public:
    IEGameStopState(QObject* parent = nullptr);
    virtual ~IEGameStopState();

    void enter(IEGame& game) override;
    void exit(IEGame& game) override;
    void onUpdateFrame() override;
    void onRenderFrame() override;
    void onResize(const float w, const float h) override;

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

