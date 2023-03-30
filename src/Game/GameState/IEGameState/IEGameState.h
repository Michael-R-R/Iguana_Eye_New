#pragma once

class IEGame;

class IEGameState
{

public:
    IEGameState() {}
    virtual ~IEGameState() {}

    virtual void enter(IEGame& game) = 0;
    virtual void exit(IEGame& game) = 0;
    virtual void onUpdateFrame(IEGame& game) = 0;
    virtual void onRenderFrame(IEGame& game) = 0;
};

