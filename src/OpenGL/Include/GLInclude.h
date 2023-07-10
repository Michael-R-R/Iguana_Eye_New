#pragma once

#include <QString>

class GLInclude
{
public:
    inline static QString includeViewProjection()
    {
        return "struct ViewProjectionStruct\n"
               "{\n"
               "\tmat4 view;\n"
               "\tmat4 projection;\n"
               "\tmat4 viewProjection;\n"
               "};\n"
               "\n"
               "layout (std140) uniform ubViewProjection\n"
               "{\n"
               "\tViewProjectionStruct uVP;\n"
               "};";
    }

    inline static QString includeCamera()
    {
        return "struct CameraStruct\n"
               "{\n"
               "\tvec4 position;\n"
               "\tvec4 rotation;\n"
               "};\n"
               "\n"
               "layout (std140) uniform ubCamera\n"
               "{\n"
               "\tCameraStruct uCamera;\n"
               "};";
    }

    inline static QString includeDirLight()
    {
        return "struct DLStruct\n"
                "{\n"
                "\tvec4 ambient;\n"
                "\tvec4 diffuse;\n"
                "\tvec4 specular;\n"
                "\tvec4 rotation;\n"
                "};\n"
                "\n"
                "layout (std140) uniform ubDirLight\n"
                "{\n"
                "\tDLStruct uDirLight;\n"
                "};";
    }

    inline static QString includePointLight()
    {
        return "struct PLStruct\n"
               "{\n"
               "\tvec4 ambient;\n"
               "\tvec4 diffuse;\n"
               "\tvec4 specular;\n"
               "\tvec4 position;\n"
               "\tvec4 CLQ;\n"
               "\tvec4 extra;\n"
               "};\n"
               "\n"
               "layout (std140) uniform ubPointLight\n"
               "{\n"
               "\tPLStruct uPointLight[100];\n"
               "};";
    }

    inline static QString includeSpotLight()
    {
        return "struct SLStruct\n"
               "{\n"
               "\tvec4 ambient;\n"
               "\tvec4 diffuse;\n"
               "\tvec4 specular;\n"
               "\tvec4 position;\n"
               "\tvec4 rotation;\n"
               "\tvec4 CLQ;\n"
               "\tvec4 cutoff;\n"
               "\tvec4 extra;\n"
               "};\n"
               "\n"
               "layout (std140) uniform ubSpotLight\n"
               "{\n"
               "\tSLStruct uSpotLight[100];\n"
               "};";
    }
};
