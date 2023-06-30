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
