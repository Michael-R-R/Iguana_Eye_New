#pragma once

#include <sol/sol.hpp>

#include "IEGameSystem.h"

class IEScriptEngine : public IEGameSystem
{
    sol::state lua;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    sol::state& getLua() { return lua; }

private:
    void setup(IEGame& game);
};

