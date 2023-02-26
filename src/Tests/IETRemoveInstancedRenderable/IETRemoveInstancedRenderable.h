#pragma once

class GameStartEvent;

class IETRemoveInstancedRenderable
{

public:
    IETRemoveInstancedRenderable(const GameStartEvent& event);
    ~IETRemoveInstancedRenderable() {}

private:
    void setup(const GameStartEvent& event);
};

