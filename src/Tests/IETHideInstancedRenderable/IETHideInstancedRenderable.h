#pragma once

class IEGame;

class IETHideInstancedRenderable
{
    int switchId;
    int hideId;

public:
    IETHideInstancedRenderable();
    ~IETHideInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

