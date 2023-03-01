#pragma once

class IEGame;

class IETRemoveInstancedRenderable
{
    int row;
    int col;
    int switchId;

public:
    IETRemoveInstancedRenderable();
    ~IETRemoveInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

