#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>

class LuaVec2Wrapper
{
    glm::vec2 vec2;

public:
    LuaVec2Wrapper();
    LuaVec2Wrapper(float n1, float n2);
    LuaVec2Wrapper(const glm::vec2& n);
    LuaVec2Wrapper(const LuaVec2Wrapper& n);
    ~LuaVec2Wrapper();

    static void addToLua(sol::state& lua);

    float x() const { return vec2[0]; }
    float y() const { return vec2[1]; }
    const glm::vec2& get() const { return vec2; }

    LuaVec2Wrapper operator +(const LuaVec2Wrapper& n) { return LuaVec2Wrapper(this->vec2 + n.vec2); }
    LuaVec2Wrapper operator -(const LuaVec2Wrapper& n) { return LuaVec2Wrapper(this->vec2 - n.vec2); }
    LuaVec2Wrapper operator /(const LuaVec2Wrapper& n) { return LuaVec2Wrapper(this->vec2 / n.vec2); }
    LuaVec2Wrapper operator *(const LuaVec2Wrapper& n) { return LuaVec2Wrapper(this->vec2 * n.vec2); }
    LuaVec2Wrapper operator *(float x) { return LuaVec2Wrapper(this->vec2 * x); }
};
