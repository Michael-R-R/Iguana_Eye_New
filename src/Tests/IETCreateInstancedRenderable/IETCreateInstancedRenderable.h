#pragma once

class IEGame;

class IETCreateInstancedRenderable
{
    int row;

public:
    IETCreateInstancedRenderable(IEGame* game);
    ~IETCreateInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

