#pragma once

#include <QDataStream>

enum class IEComponentType : unsigned long long
{
    Input = 1,              // implemeneted
    Transform = 2,          //
    Camera = 4,             //
    CameraController = 8,   //
    Material = 16,          //
    Mesh = 32,              //
    Shader = 64,            //
    Renderable = 128,       //
    Physics = 256,          //
    Hierarchy = 512         // implemeneted
};
