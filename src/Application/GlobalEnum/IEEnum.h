#pragma once

enum class IEColorType
{
    Ambient, Diffuse, Specular,
    Emissive, Reflective, Transparent
};

enum class IETextureType
{
    Ambient, Diffuse, Specular,
    Normals, Height, Emissive,
    Shininess, Opacity, Displacement,
    Lightmap, Unknown
};

enum class IEBufferType
{
    Index, Vec2, Vec3, Vec4, Mat4, Unknown
};
