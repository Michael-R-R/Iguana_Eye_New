#include "LuaCommonType.h"
#include "LuaVec2Wrapper.h"
#include "LuaVec3Wrapper.h"
#include "LuaVec4Wrapper.h"
#include "LuaMat4Wrapper.h"

LuaCommonType::LuaCommonType(sol::state& lua)
{
    LuaVec2Wrapper::addToLua(lua);
    LuaVec3Wrapper::addToLua(lua);
    LuaVec4Wrapper::addToLua(lua);
    LuaMat4Wrapper::addToLua(lua);
}

LuaCommonType::~LuaCommonType()
{

}
