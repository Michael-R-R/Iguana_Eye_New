#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEGameSystem.h"

class IEScriptEngine : public IEGameSystem
{
    IEScriptEngine();
    static IEScriptEngine mInstance;

    sol::state lua;

public:
    static IEScriptEngine& instance();
    ~IEScriptEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    sol::state& getLua() { return lua; }

private:
    void setup(IEGame& game);
};

