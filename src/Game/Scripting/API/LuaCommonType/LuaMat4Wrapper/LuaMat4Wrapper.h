#pragma once

#include <QMatrix4x4>
#include <QVector3D>

class LuaMat4Wrapper
{
    QMatrix4x4 mat4;

public:
    LuaMat4Wrapper() : mat4() {}
    LuaMat4Wrapper(const QMatrix4x4& n) : mat4(n) {}
    LuaMat4Wrapper(const LuaMat4Wrapper& n) : mat4(n.mat4) {}
    ~LuaMat4Wrapper() {}

    QMatrix4x4 inverted(bool* invertible = nullptr) { return mat4.inverted(invertible); }
    void lookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up) { mat4.lookAt(eye, center, up); }
    void ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane) { mat4.ortho(left, right, bottom, top, nearPlane, farPlane); }
    void perspective(float verticalAngle, float aspectRatio, float nearPlane, float farPlane) { mat4.perspective(verticalAngle, aspectRatio, nearPlane, farPlane); }
    void rotate(float angle, float x, float y, float z = 0.0f) { mat4.rotate(angle, x, y, z); }
    void scale(float x, float y, float z) { mat4.scale(x, y, z); }
    void translate(float x, float y, float z) { mat4.translate(x, y, z); }
    void setToIdentity() { mat4.setToIdentity(); }
    QMatrix4x4& get() { return mat4; }

    LuaMat4Wrapper operator +(const LuaMat4Wrapper& n)
    {
        return LuaMat4Wrapper(this->mat4 + n.mat4);
    }

    LuaMat4Wrapper operator -(const LuaMat4Wrapper& n)
    {
        return LuaMat4Wrapper(this->mat4 - n.mat4);
    }

    LuaMat4Wrapper operator *(const LuaMat4Wrapper& n)
    {
        return LuaMat4Wrapper(this->mat4 * n.mat4);
    }
};
