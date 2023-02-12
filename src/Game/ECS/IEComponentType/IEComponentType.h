#pragma once

#include <QDataStream>

enum class IEComponentType : unsigned long long
{
    Input = 1,              // implemented
    Transform = 2,          // implemented
    Camera = 4,             //
    CameraController = 8,   //
    Material = 16,          // implemented
    Mesh = 32,              // implemented
    Shader = 64,            // implemented
    Renderable = 128,       // implemented
    Physics = 256,          //
    Hierarchy = 512         // implemented
};
