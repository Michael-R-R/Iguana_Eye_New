#pragma once

#include <QVector3D>

class LuaVec3Wrapper
{
    QVector3D vec3;

public:
    LuaVec3Wrapper() : vec3() {}
    LuaVec3Wrapper(float n1, float n2, float n3) : vec3(n1, n2, n3) {}
    LuaVec3Wrapper(const QVector3D& n) : vec3(n) {}
    LuaVec3Wrapper(const LuaVec3Wrapper& n) : vec3(n.vec3) {}
    ~LuaVec3Wrapper() {}

    float x() const { return vec3.x(); }
    float y() const { return vec3.y(); }
    float z() const { return vec3.z(); }
    QVector3D& get() { return vec3; }

    LuaVec3Wrapper normalize()
    {
        vec3.normalize();
        return LuaVec3Wrapper(vec3);
    }

    LuaVec3Wrapper cross(LuaVec3Wrapper v1, LuaVec3Wrapper v2)
    {
        vec3 = QVector3D::crossProduct(v1.vec3, v2.vec3);
        return LuaVec3Wrapper(vec3);
    }

    LuaVec3Wrapper operator +(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 + n.vec3);
    }

    LuaVec3Wrapper operator -(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 - n.vec3);
    }

    LuaVec3Wrapper operator *(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 * n.vec3);
    }

    LuaVec3Wrapper operator *(float x)
    {
        return LuaVec3Wrapper(this->vec3 * x);
    }

    LuaVec3Wrapper operator /(const LuaVec3Wrapper& n)
    {
        return LuaVec3Wrapper(this->vec3 / n.vec3);
    }
};
