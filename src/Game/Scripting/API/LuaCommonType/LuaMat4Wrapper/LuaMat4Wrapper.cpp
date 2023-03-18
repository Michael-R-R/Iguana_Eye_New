#include "LuaMat4Wrapper.h"

LuaMat4Wrapper::LuaMat4Wrapper() :
    mat4()
{

}

LuaMat4Wrapper::LuaMat4Wrapper(const QMatrix4x4& n) :
    mat4(n)
{

}

LuaMat4Wrapper::LuaMat4Wrapper(const LuaMat4Wrapper& n) :
    mat4(n.mat4)
{

}

LuaMat4Wrapper::~LuaMat4Wrapper()
{

}

void LuaMat4Wrapper::addToLua(sol::state& lua)
{
    lua.new_usertype<LuaMat4Wrapper>("Mat4", sol::constructors<LuaMat4Wrapper(),
                                     LuaMat4Wrapper(const QMatrix4x4&),
                                     LuaMat4Wrapper(const LuaMat4Wrapper&)>(),
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

QMatrix4x4 LuaMat4Wrapper::inverted(bool* invertible)
{
    return mat4.inverted(invertible);
}

void LuaMat4Wrapper::lookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up)
{
    mat4.lookAt(eye, center, up);
}

void LuaMat4Wrapper::ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    mat4.ortho(left, right, bottom, top, nearPlane, farPlane);
}

void LuaMat4Wrapper::perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane)
{
    mat4.perspective(verticalAngle, aspectRatio, nearPlane, farPlane);
}

void LuaMat4Wrapper::rotate(float angle, float x, float y, float z)
{
    mat4.rotate(angle, x, y, z);
}

void LuaMat4Wrapper::scale(float x, float y, float z)
{
    mat4.scale(x, y, z);
}

void LuaMat4Wrapper::translate(float x, float y, float z)
{
    mat4.translate(x, y, z);
}

void LuaMat4Wrapper::setToIdentity()
{
    mat4.setToIdentity();
}

QMatrix4x4& LuaMat4Wrapper::get()
{
    return mat4;
}
