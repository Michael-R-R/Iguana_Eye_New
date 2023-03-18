#include "LuaCommonType.h"
#include "LuaVec2Wrapper.h"
#include "LuaVec3Wrapper.h"
#include "LuaVec4Wrapper.h"
#include "LuaMat4Wrapper.h"

LuaCommonType::LuaCommonType(sol::state& lua)
{
    lua.new_usertype<LuaVec2Wrapper>("Vec2", sol::constructors<LuaVec2Wrapper(), LuaVec2Wrapper(float, float)>(),
                                     "x", &LuaVec2Wrapper::x,
                                     "y", &LuaVec2Wrapper::y,
                                     sol::meta_function::addition, &LuaVec2Wrapper::addition,
                                     sol::meta_function::subtraction, &LuaVec2Wrapper::subtraction,
                                     sol::meta_function::multiplication, &LuaVec2Wrapper::multiply,
                                     sol::meta_function::division, &LuaVec2Wrapper::division);

    lua.new_usertype<LuaVec3Wrapper>("Vec3", sol::constructors<LuaVec3Wrapper(), LuaVec3Wrapper(float, float, float)>(),
                                     "x", &LuaVec3Wrapper::x,
                                     "y", &LuaVec3Wrapper::y,
                                     "z", &LuaVec3Wrapper::z,
                                     sol::meta_function::addition, &LuaVec3Wrapper::addition,
                                     sol::meta_function::subtraction, &LuaVec3Wrapper::subtraction,
                                     sol::meta_function::multiplication, &LuaVec3Wrapper::multiply,
                                     sol::meta_function::division, &LuaVec3Wrapper::division);

    lua.new_usertype<LuaVec4Wrapper>("Vec4", sol::constructors<LuaVec4Wrapper(), LuaVec4Wrapper(float, float, float, float)>(),
                                     "x", &LuaVec4Wrapper::x,
                                     "y", &LuaVec4Wrapper::y,
                                     "z", &LuaVec4Wrapper::z,
                                     "w", &LuaVec4Wrapper::w,
                                     sol::meta_function::addition, &LuaVec4Wrapper::addition,
                                     sol::meta_function::subtraction, &LuaVec4Wrapper::subtraction,
                                     sol::meta_function::multiplication, &LuaVec4Wrapper::multiply,
                                     sol::meta_function::division, &LuaVec4Wrapper::division);

    lua.new_usertype<LuaMat4Wrapper>("Mat4", sol::constructors<LuaMat4Wrapper()>(),
                                     "inverted", &LuaMat4Wrapper::inverted,
                                     "lookAt", &LuaMat4Wrapper::lookAt,
                                     "ortho", &LuaMat4Wrapper::ortho,
                                     "perspective", &LuaMat4Wrapper::perspective,
                                     "rotate", &LuaMat4Wrapper::rotate,
                                     "scale", &LuaMat4Wrapper::scale,
                                     "translate", &LuaMat4Wrapper::translate,
                                     "setToIdentity", &LuaMat4Wrapper::setToIdentity,
                                     sol::meta_function::addition, &LuaMat4Wrapper::addition,
                                     sol::meta_function::subtraction, &LuaMat4Wrapper::subtraction,
                                     sol::meta_function::multiplication, &LuaMat4Wrapper::multiply);
}

LuaCommonType::~LuaCommonType()
{

}
