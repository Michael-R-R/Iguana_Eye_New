#pragma once

class IEGame;

class IETCreateInstancedRenderable
{
    int row;
    int col;
    unsigned long long renderableId;

public:
    IETCreateInstancedRenderable(IEGame* game);
    ~IETCreateInstancedRenderable() {}

    void run(IEGame* game);
    void oneShot(IEGame* game);
};

