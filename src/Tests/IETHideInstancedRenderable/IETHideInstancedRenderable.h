#pragma once

class GameStartEvent;

class IETHideInstancedRenderable
{

public:
    IETHideInstancedRenderable(const GameStartEvent& event);
    ~IETHideInstancedRenderable() {}

private:
    void setup(const GameStartEvent& event);

};

