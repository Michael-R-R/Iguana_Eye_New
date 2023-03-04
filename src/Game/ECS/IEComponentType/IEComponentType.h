#pragma once

#include <QDataStream>

enum class IEComponentType : unsigned long long
{
    Name = 1,                // implemented
    Hierarchy = 2,           // implemented
    Input = 4,               // implemented
    Transform = 8,           // implemented
    Physics = 16,            //
    Camera = 32,             // implemented
    CameraController = 64,   //
    Mesh = 128,              // implemented
    Material = 256,          // implemented
    Shader = 512,            // implemented
    Renderable = 1024,       // implemented
};
