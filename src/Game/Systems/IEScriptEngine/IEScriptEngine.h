#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEObject.h"

class GameStartEvent;

class IEScriptEngine : public IEObject
{
    sol::state lua;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }
};

