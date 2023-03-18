#pragma once

#include <QVector4D>

class LuaVec4Wrapper
{
    QVector4D vec4;

public:
    LuaVec4Wrapper() : vec4() {}
    LuaVec4Wrapper(float n1, float n2, float n3, float n4) : vec4(n1, n2, n3, n4) {}
    LuaVec4Wrapper(const QVector4D& n) : vec4(n) {}
    LuaVec4Wrapper(const LuaVec4Wrapper& n) : vec4(n.vec4) {}
    ~LuaVec4Wrapper() {}

    float x() const { return vec4.x(); }
    float y() const { return vec4.y(); }
    float z() const { return vec4.z(); }
    float w() const { return vec4.w(); }
    QVector4D get() { return vec4; }

    LuaVec4Wrapper operator +(const LuaVec4Wrapper& n)
    {
        return LuaVec4Wrapper(this->vec4 + n.vec4);
    }

    LuaVec4Wrapper operator -(const LuaVec4Wrapper& n)
    {
        return LuaVec4Wrapper(this->vec4 - n.vec4);
    }

    LuaVec4Wrapper operator *(const LuaVec4Wrapper& n)
    {
        return LuaVec4Wrapper(this->vec4 * n.vec4);
    }

    LuaVec4Wrapper operator *(float x)
    {
        return LuaVec4Wrapper(this->vec4 * x);
    }

    LuaVec4Wrapper operator /(const LuaVec4Wrapper& n)
    {
        return LuaVec4Wrapper(this->vec4 / n.vec4);
    }
};
