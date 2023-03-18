#pragma once

#include <QVector3D>

class LuaVec3Wrapper
{
    QVector3D vec3;

public:
    LuaVec3Wrapper() : vec3() {}
    LuaVec3Wrapper(float n1, float n2, float n3) : vec3(n1, n2, n3) {}
    LuaVec3Wrapper(const QVector3D& n) : vec3(n) {}
    ~LuaVec3Wrapper() {}

    float x() const { return vec3.x(); }
    float y() const { return vec3.y(); }
    float z() const { return vec3.z(); }

    LuaVec3Wrapper addition(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 + n.vec3);
    }

    LuaVec3Wrapper subtraction(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 - n.vec3);
    }

    LuaVec3Wrapper multiply(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 * n.vec3);
    }

    LuaVec3Wrapper division(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 / n.vec3);
    }
};
