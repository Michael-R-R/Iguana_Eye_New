#pragma once

#include <QDataStream>

enum class IEComponentType : unsigned long long
{
    Hierarchy = 1,           // implemented
    Input = 2,               // implemented
    Transform = 4,           // implemented
    Physics = 8,             //
    Camera = 16,             //
    CameraController = 32,   //
    Mesh = 64,               // implemented
    Material = 128,          // implemented
    Shader = 256,            // implemented
    Renderable = 512,        // implemented
};
