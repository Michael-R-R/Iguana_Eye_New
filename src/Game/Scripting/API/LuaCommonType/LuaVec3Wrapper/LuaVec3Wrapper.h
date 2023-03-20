#pragma once

#include <sol/sol.hpp>

#include <QVector3D>
#include <QVector4D>

class LuaVec3Wrapper
{
    QVector3D vec3;

public:
    LuaVec3Wrapper();
    LuaVec3Wrapper(float n1, float n2, float n3);
    LuaVec3Wrapper(const QVector3D& n);
    LuaVec3Wrapper(const QVector4D& n);
    LuaVec3Wrapper(const LuaVec3Wrapper& n);
    ~LuaVec3Wrapper();

    static void addToLua(sol::state& lua);

    float x() const { return vec3.x(); }
    float y() const { return vec3.y(); }
    float z() const { return vec3.z(); }
    QVector3D& get() { return vec3; }

    LuaVec3Wrapper normalize();
    LuaVec3Wrapper cross(LuaVec3Wrapper v1, LuaVec3Wrapper v2);

    LuaVec3Wrapper operator +(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 + n.vec3); }
    LuaVec3Wrapper operator -(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 - n.vec3); }
    LuaVec3Wrapper operator /(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 / n.vec3); }
    LuaVec3Wrapper operator *(const LuaVec3Wrapper& n) { return LuaVec3Wrapper(this->vec3 * n.vec3); }
    LuaVec3Wrapper operator *(float x) { return LuaVec3Wrapper(this->vec3 * x); }
};
