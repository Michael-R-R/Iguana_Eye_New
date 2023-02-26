#pragma once

class GameStartEvent;

class IETCreateInstancedRenderable
{

public:
    IETCreateInstancedRenderable(const GameStartEvent& event);
    ~IETCreateInstancedRenderable() {}

private:
    void setup(const GameStartEvent& event);
};

