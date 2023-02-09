#pragma once

#include <QDataStream>

enum class IEComponentType : unsigned long long
{
    Input = 1,              //
    Transform = 2,          //
    Camera = 4,             //
    CameraController = 8,   //
    Material = 16,          //
    Mesh = 32,              //
    Shader = 64,            //
    Renderable = 128,       //
    Physics = 256,          //
    ParentChild = 512       //
};
