#pragma once

#include <sol/sol.hpp>

#include "IEGameSystem.h"

class IEScriptEngine : public IEGameSystem
{
    sol::state lua;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    sol::state& getLua() { return lua; }

private:
    void setup(IEGame& game);
};

