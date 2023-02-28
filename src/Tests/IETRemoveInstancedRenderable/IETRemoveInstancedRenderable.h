#pragma once

class IEGame;

class IETRemoveInstancedRenderable
{
    int row;

public:
    IETRemoveInstancedRenderable();
    ~IETRemoveInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

