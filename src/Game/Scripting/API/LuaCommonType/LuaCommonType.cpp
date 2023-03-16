#include "LuaCommonType.h"
#include <QVector2D>
#include <QVector4D>
#include <QMatrix4x4>
#include "LuaVec3Wrapper.h"

LuaCommonType::LuaCommonType(sol::state& lua)
{
    lua.new_usertype<QVector2D>("Vec2", sol::constructors<QVector2D(), QVector2D(float, float)>(),
                                "x", &QVector2D::x,
                                "y", &QVector2D::y);

    lua.new_usertype<LuaVec3Wrapper>("Vec3", sol::constructors<LuaVec3Wrapper(), LuaVec3Wrapper(float, float, float)>(),
                                  "x", &LuaVec3Wrapper::x,
                                  "y", &LuaVec3Wrapper::y,
                                  "z", &LuaVec3Wrapper::z,
                                  sol::meta_function::addition, &LuaVec3Wrapper::addition,
                                  sol::meta_function::subtraction, &LuaVec3Wrapper::subtraction,
                                  sol::meta_function::multiplication, &LuaVec3Wrapper::multiply,
                                  sol::meta_function::division, &LuaVec3Wrapper::division);

    lua.new_usertype<QVector4D>("Vec4", sol::constructors<QVector4D(), QVector4D(float, float, float, float)>(),
                                "x", &QVector4D::x,
                                "y", &QVector4D::y,
                                "z", &QVector4D::z,
                                "w", &QVector4D::w);

    lua.new_usertype<QMatrix4x4>("Mat4", sol::constructors<QMatrix4x4()>(),
                                 "inverted", &QMatrix4x4::inverted,
                                 "lookAt", &QMatrix4x4::lookAt,
                                 "ortho", sol::resolve<float, float, float, float, float, float>(&QMatrix4x4::ortho),
                                 "perspective", &QMatrix4x4::perspective,
                                 "rotate", sol::resolve<float, float, float, float>(&QMatrix4x4::rotate),
                                 "scale", sol::resolve<float, float, float>(&QMatrix4x4::scale),
                                 "translate", sol::resolve<float, float, float>(&QMatrix4x4::translate),
                                 "setToIdentity", &QMatrix4x4::setToIdentity);
}
