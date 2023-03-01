#pragma once

class IEGame;

class IETCreateInstancedRenderable
{
    int row;
    int col;

public:
    IETCreateInstancedRenderable(IEGame* game);
    ~IETCreateInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

