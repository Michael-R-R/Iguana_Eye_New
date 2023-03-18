#pragma once

#include <sol/sol.hpp>
#include <QMatrix4x4>
#include <QVector3D>

class LuaMat4Wrapper
{
    QMatrix4x4 mat4;

public:
    LuaMat4Wrapper();
    LuaMat4Wrapper(const QMatrix4x4& n);
    LuaMat4Wrapper(const LuaMat4Wrapper& n);
    ~LuaMat4Wrapper();

    static void addToLua(sol::state& lua);

    QMatrix4x4 inverted(bool* invertible = nullptr);
    void lookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up);
    void ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    void perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane);
    void rotate(float angle, float x, float y, float z = 0.0f);
    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void setToIdentity();
    QMatrix4x4& get();

    LuaMat4Wrapper operator +(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->mat4 + n.mat4); }
    LuaMat4Wrapper operator -(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->mat4 - n.mat4); }
    LuaMat4Wrapper operator *(const LuaMat4Wrapper& n) { return LuaMat4Wrapper(this->mat4 * n.mat4); }
};
