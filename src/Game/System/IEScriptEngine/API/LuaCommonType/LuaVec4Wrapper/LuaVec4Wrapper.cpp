#include "LuaVec4Wrapper.h"

LuaVec4Wrapper::LuaVec4Wrapper() :
    vec4()
{

}

LuaVec4Wrapper::LuaVec4Wrapper(float n1, float n2, float n3, float n4) :
    vec4(n1, n2, n3, n4)
{

}

LuaVec4Wrapper::LuaVec4Wrapper(const glm::vec4& n) :
    vec4(n)
{

}

LuaVec4Wrapper::LuaVec4Wrapper(const LuaVec4Wrapper& n) :
    vec4(n.vec4)
{

}

LuaVec4Wrapper::~LuaVec4Wrapper()
{

}

void LuaVec4Wrapper::addToLua(sol::state& lua)
{
    lua.new_usertype<LuaVec4Wrapper>("IEVec4", sol::constructors<LuaVec4Wrapper(),
                                     LuaVec4Wrapper(float, float, float, float),
                                     LuaVec4Wrapper(const glm::vec4&),
                                     LuaVec4Wrapper(const LuaVec4Wrapper&)>(),
                                     "x", &LuaVec4Wrapper::x,
                                     "y", &LuaVec4Wrapper::y,
                                     "z", &LuaVec4Wrapper::z,
                                     "w", &LuaVec4Wrapper::w,
                                     "get", &LuaVec4Wrapper::get,
                                     sol::meta_function::addition, &LuaVec4Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaVec4Wrapper::operator -,
                                     sol::meta_function::multiplication, sol::overload(sol::resolve<const LuaVec4Wrapper&>(&LuaVec4Wrapper::operator *),
                                                                                       sol::resolve<float>(&LuaVec4Wrapper::operator *)),
                                     sol::meta_function::division, &LuaVec4Wrapper::operator /);
}
