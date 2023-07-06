#pragma once

#include <sol/sol.hpp>

#include "IESystem.h"

class IEScriptEngine : public IESystem
{
    sol::state lua;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;

    sol::state& getLua() { return lua; }

private:
    void setup(IEGame& game);
};

