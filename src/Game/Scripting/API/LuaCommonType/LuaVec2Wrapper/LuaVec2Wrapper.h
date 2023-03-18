#pragma once

#include <QVector2D>

class LuaVec2Wrapper
{
    QVector2D vec2;

public:
    LuaVec2Wrapper() : vec2() {}
    LuaVec2Wrapper(float n1, float n2) : vec2(n1, n2) {}
    LuaVec2Wrapper(const QVector2D& n) : vec2(n) {}
    LuaVec2Wrapper(const LuaVec2Wrapper& n) : vec2(n.vec2) {}
    ~LuaVec2Wrapper() {}

    float x() const { return vec2.x(); }
    float y() const { return vec2.y(); }
    QVector2D& get() { return vec2; }

    LuaVec2Wrapper operator +(const LuaVec2Wrapper& n)
    {
        return LuaVec2Wrapper(this->vec2 + n.vec2);
    }

    LuaVec2Wrapper operator -(const LuaVec2Wrapper& n)
    {
        return LuaVec2Wrapper(this->vec2 - n.vec2);
    }

    LuaVec2Wrapper operator *(const LuaVec2Wrapper& n)
    {
        return LuaVec2Wrapper(this->vec2 * n.vec2);
    }

    LuaVec2Wrapper operator *(float x)
    {
        return LuaVec2Wrapper(this->vec2 * x);
    }

    LuaVec2Wrapper operator /(const LuaVec2Wrapper& n)
    {
        return LuaVec2Wrapper(this->vec2 / n.vec2);
    }
};
