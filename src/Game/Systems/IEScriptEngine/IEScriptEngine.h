#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEObject.h"

class GameStartEvent;
class LuaUtility;
class LuaEnum;
class LuaCommonType;
class LuaIETime;
class LuaIEInput;
class LuaIEECS;
class LuaIEECSInputSystem;
class LuaIEECSScriptSystem;
class LuaIEECSTransformSystem;
class LuaIEECSCameraSystem;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    std::unique_ptr<LuaEnum> luaEnum;
    std::unique_ptr<LuaCommonType> luaCommonType;
    std::unique_ptr<LuaUtility> luaUtility;
    std::unique_ptr<LuaIETime> luaTime;
    std::unique_ptr<LuaIEInput> luaInput;
    std::unique_ptr<LuaIEECS> luaECS;
    std::unique_ptr<LuaIEECSInputSystem> luaInputSystem;
    std::unique_ptr<LuaIEECSScriptSystem> luaScriptSystem;
    std::unique_ptr<LuaIEECSTransformSystem> luaTransformSystem;
    std::unique_ptr<LuaIEECSCameraSystem> luaCameraSystem;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }
};

