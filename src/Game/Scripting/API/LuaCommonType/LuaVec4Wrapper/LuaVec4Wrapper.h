#pragma once

#include <sol/sol.hpp>

#include <QVector4D>

class LuaVec4Wrapper
{
    QVector4D vec4;

public:
    LuaVec4Wrapper();
    LuaVec4Wrapper(float n1, float n2, float n3, float n4);
    LuaVec4Wrapper(const QVector4D& n);
    LuaVec4Wrapper(const LuaVec4Wrapper& n);
    ~LuaVec4Wrapper();

    static void addToLua(sol::state& lua);

    float x() const { return vec4.x(); }
    float y() const { return vec4.y(); }
    float z() const { return vec4.z(); }
    float w() const { return vec4.w(); }
    QVector4D& get() { return vec4; }

    LuaVec4Wrapper operator +(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 + n.vec4); }
    LuaVec4Wrapper operator -(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 - n.vec4); }
    LuaVec4Wrapper operator /(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 / n.vec4); }
    LuaVec4Wrapper operator *(const LuaVec4Wrapper& n) { return LuaVec4Wrapper(this->vec4 * n.vec4); }
    LuaVec4Wrapper operator *(float x) { return LuaVec4Wrapper(this->vec4 * x); }
};
