#pragma once

class IEGame;

class IETHideInstancedRenderable
{

public:
    IETHideInstancedRenderable();
    ~IETHideInstancedRenderable() {}

    void oneShot(IEGame* game);
};

