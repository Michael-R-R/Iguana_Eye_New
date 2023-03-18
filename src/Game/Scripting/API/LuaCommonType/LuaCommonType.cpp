#include "LuaCommonType.h"
#include "LuaVec2Wrapper.h"
#include "LuaVec3Wrapper.h"
#include "LuaVec4Wrapper.h"
#include "LuaMat4Wrapper.h"

LuaCommonType::LuaCommonType(sol::state& lua)
{
    lua.new_usertype<LuaVec2Wrapper>("Vec2", sol::constructors<LuaVec2Wrapper(), LuaVec2Wrapper(float, float), LuaVec2Wrapper(const QVector2D&), LuaVec2Wrapper(const LuaVec2Wrapper&)>(),
                                     "x", &LuaVec2Wrapper::x,
                                     "y", &LuaVec2Wrapper::y,
                                     "get", &LuaVec2Wrapper::get,
                                     sol::meta_function::addition, &LuaVec2Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaVec2Wrapper::operator -,
                                     sol::meta_function::multiplication, sol::overload(sol::resolve<const LuaVec2Wrapper&>(&LuaVec2Wrapper::operator *),
                                                                                       sol::resolve<float>(&LuaVec2Wrapper::operator *)),
                                     sol::meta_function::division, &LuaVec2Wrapper::operator /);

    lua.new_usertype<LuaVec3Wrapper>("Vec3", sol::constructors<LuaVec3Wrapper(), LuaVec3Wrapper(float, float, float), LuaVec3Wrapper(const QVector3D&), LuaVec3Wrapper(const LuaVec3Wrapper&)>(),
                                     "x", &LuaVec3Wrapper::x,
                                     "y", &LuaVec3Wrapper::y,
                                     "z", &LuaVec3Wrapper::z,
                                     "normalize", &LuaVec3Wrapper::normalize,
                                     "cross", &LuaVec3Wrapper::cross,
                                     "get", &LuaVec3Wrapper::get,
                                     sol::meta_function::addition, &LuaVec3Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaVec3Wrapper::operator -,
                                     sol::meta_function::multiplication, sol::overload(sol::resolve<const LuaVec3Wrapper&>(&LuaVec3Wrapper::operator *),
                                                                                       sol::resolve<float>(&LuaVec3Wrapper::operator *)),
                                     sol::meta_function::division, &LuaVec3Wrapper::operator /);

    lua.new_usertype<LuaVec4Wrapper>("Vec4", sol::constructors<LuaVec4Wrapper(), LuaVec4Wrapper(float, float, float, float), LuaVec4Wrapper(const QVector4D&), LuaVec4Wrapper(const LuaVec4Wrapper&)>(),
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

    lua.new_usertype<LuaMat4Wrapper>("Mat4", sol::constructors<LuaMat4Wrapper(), LuaMat4Wrapper(const QMatrix4x4&), LuaMat4Wrapper(const LuaMat4Wrapper&)>(),
                                     "inverted", &LuaMat4Wrapper::inverted,
                                     "lookAt", &LuaMat4Wrapper::lookAt,
                                     "ortho", &LuaMat4Wrapper::ortho,
                                     "perspective", &LuaMat4Wrapper::perspective,
                                     "rotate", &LuaMat4Wrapper::rotate,
                                     "scale", &LuaMat4Wrapper::scale,
                                     "translate", &LuaMat4Wrapper::translate,
                                     "setToIdentity", &LuaMat4Wrapper::setToIdentity,
                                     "get", &LuaMat4Wrapper::get,
                                     sol::meta_function::addition, &LuaMat4Wrapper::operator +,
                                     sol::meta_function::subtraction, &LuaMat4Wrapper::operator -,
                                     sol::meta_function::multiplication, &LuaMat4Wrapper::operator *);
}

LuaCommonType::~LuaCommonType()
{

}
