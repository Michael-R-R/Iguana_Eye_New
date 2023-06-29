#include "LuaVec2Wrapper.h"

LuaVec2Wrapper::LuaVec2Wrapper() :
    vec2()
{

}

LuaVec2Wrapper::LuaVec2Wrapper(float n1, float n2) :
    vec2(n1, n2)
{

}

LuaVec2Wrapper::LuaVec2Wrapper(const QVector2D& n) :
    vec2(n)
{

}

LuaVec2Wrapper::LuaVec2Wrapper(const LuaVec2Wrapper& n) :
    vec2(n.vec2)
{

}

LuaVec2Wrapper::~LuaVec2Wrapper()
{

}

void LuaVec2Wrapper::addToLua(sol::state& lua)
{
    lua.new_usertype<LuaVec2Wrapper>("IEVec2", sol::constructors<LuaVec2Wrapper(),
                                     LuaVec2Wrapper(float, float),
                                     LuaVec2Wrapper(const QVector2D&),
                                     LuaVec2Wrapper(const LuaVec2Wrapper&)>(),
                                     "x", &LuaVec2Wrapper::x,
                                     "y", &LuaVec2Wrapper::y,
                                     "get", &LuaVec2Wrapper::get,
                                     sol::meta_function::addition, &LuaVec2Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaVec2Wrapper::operator -,
                                     sol::meta_function::multiplication, sol::overload(sol::resolve<const LuaVec2Wrapper&>(&LuaVec2Wrapper::operator *),
                                                                                       sol::resolve<float>(&LuaVec2Wrapper::operator *)),
                                     sol::meta_function::division, &LuaVec2Wrapper::operator /);
}

