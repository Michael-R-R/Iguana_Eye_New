#pragma once

class IEGame;

class IEGameState
{

public:
    IEGameState() {}
    virtual ~IEGameState() {}

    virtual void enter(IEGame& game) = 0;
    virtual void exit(IEGame& game) = 0;
    virtual void onUpdateFrame() = 0;
    virtual void onRenderFrame() = 0;
    virtual void onResize(const float w, const float h) = 0;
};

