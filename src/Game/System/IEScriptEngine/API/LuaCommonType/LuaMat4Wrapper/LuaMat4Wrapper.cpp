#include "LuaMat4Wrapper.h"
#include <glm/gtc/matrix_transform.hpp>

LuaMat4Wrapper::LuaMat4Wrapper() :
    value()
{

}

LuaMat4Wrapper::LuaMat4Wrapper(const glm::mat4& n) :
    value(n)
{

}

LuaMat4Wrapper::LuaMat4Wrapper(const LuaMat4Wrapper& n) :
    value(n.value)
{

}

LuaMat4Wrapper::~LuaMat4Wrapper()
{

}

void LuaMat4Wrapper::addToLua(sol::state& lua)
{
    lua.new_usertype<LuaMat4Wrapper>("IEMat4", sol::constructors<LuaMat4Wrapper(),
                                     LuaMat4Wrapper(const glm::mat4&),
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

glm::mat4 LuaMat4Wrapper::inverted()
{
    return glm::inverse(value);
}

void LuaMat4Wrapper::lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
    value = glm::lookAt(eye, center, up);
}

void LuaMat4Wrapper::ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    value = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

void LuaMat4Wrapper::perspective(float fov, float aspect, float nearPlane, float farPlane)
{
    value = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void LuaMat4Wrapper::rotate(float angle, float x, float y, float z)
{
    value = glm::rotate(value, glm::radians(angle), glm::vec3(x, y, z));
}

void LuaMat4Wrapper::scale(float x, float y, float z)
{
    value = glm::scale(value, glm::vec3(x, y, z));
}

void LuaMat4Wrapper::translate(float x, float y, float z)
{
    value = glm::translate(value, glm::vec3(x, y, z));
}

void LuaMat4Wrapper::setToIdentity()
{
    value = glm::mat4(1.0f);
}

glm::mat4& LuaMat4Wrapper::get()
{
    return value;
}
