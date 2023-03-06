#pragma once

enum class IEComponentType : unsigned long long
{
    Name = 1,                // implemented
    Hierarchy = 2,           // implemented
    Input = 4,               // implemented
    Script = 8,              //
    Physics = 16,            //
    Transform = 32,          // implemented
    Camera = 64,             // implemented
    Mesh = 128,              // implemented
    Material = 256,          // implemented
    Shader = 512,            // implemented
    Renderable = 1024,       // implemented
};
