#pragma once

#include <memory>

class GameStartEvent;

class IETCreateRenderable
{

public:
    IETCreateRenderable(const GameStartEvent& event);
    ~IETCreateRenderable();
};

