#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEObject.h"

class IEGame;

class IEScriptEngine : public IEObject
{
    sol::state lua;

public:
    IEScriptEngine(IEGame& game);
    ~IEScriptEngine();

    sol::state& getLua() { return lua; }
};

