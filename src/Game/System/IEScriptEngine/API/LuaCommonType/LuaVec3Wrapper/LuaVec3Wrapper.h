#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>

class LuaVec3Wrapper
{
    glm::vec3 vec3;

public:
    LuaVec3Wrapper();
    LuaVec3Wrapper(float n1, float n2, float n3);
    LuaVec3Wrapper(const glm::vec3& n);
    LuaVec3Wrapper(const glm::vec4& n);
    LuaVec3Wrapper(const LuaVec3Wrapper& n);
    ~LuaVec3Wrapper();

    static void addToLua(sol::state& lua);

    float x() const { return vec3[0]; }
    float y() const { return vec3[1]; }
    float z() const { return vec3[2]; }
    const glm::vec3& get() const { return vec3; }

    LuaVec3Wrapper normalize();
    LuaVec3Wrapper cross(LuaVec3Wrapper v1, LuaVec3Wrapper v2);

    LuaVec3Wrapper operator +(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 + n.vec3); }
    LuaVec3Wrapper operator -(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 - n.vec3); }
    LuaVec3Wrapper operator /(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 / n.vec3); }
    LuaVec3Wrapper operator *(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 * n.vec3); }
    LuaVec3Wrapper operator *(float x) { return LuaVec3Wrapper(this->vec3 * x); }
};
