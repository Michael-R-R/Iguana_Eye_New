#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>

class LuaVec4Wrapper
{
    glm::vec4 vec4;

public:
    LuaVec4Wrapper();
    LuaVec4Wrapper(float n1, float n2, float n3, float n4);
    LuaVec4Wrapper(const glm::vec4& n);
    LuaVec4Wrapper(const LuaVec4Wrapper& n);
    ~LuaVec4Wrapper();

    static void addToLua(sol::state& lua);

    float x() const { return vec4[0]; }
    float y() const { return vec4[1]; }
    float z() const { return vec4[2]; }
    float w() const { return vec4[3]; }
    const glm::vec4& get() const { return vec4; }

    LuaVec4Wrapper operator +(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 + n.vec4); }
    LuaVec4Wrapper operator -(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 - n.vec4); }
    LuaVec4Wrapper operator /(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 / n.vec4); }
    LuaVec4Wrapper operator *(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 * n.vec4); }
    LuaVec4Wrapper operator *(float x) { return LuaVec4Wrapper(this->vec4 * x); }
};
