#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>

class LuaMat4Wrapper
{
    glm::mat4 value;

public:
    LuaMat4Wrapper();
    LuaMat4Wrapper(const glm::mat4& n);
    LuaMat4Wrapper(const LuaMat4Wrapper& n);
    ~LuaMat4Wrapper();

    static void addToLua(sol::state& lua);

    glm::mat4 inverted();
    void lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);
    void ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    void perspective(float fov, float aspect, float nearPlane, float farPlane);
    void rotate(float angle, float x, float y, float z = 0.0f);
    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void setToIdentity();
    glm::mat4& get();

    LuaMat4Wrapper operator +(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->value + n.value); }
    LuaMat4Wrapper operator -(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->value - n.value); }
    LuaMat4Wrapper operator *(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->value * n.value); }
};
