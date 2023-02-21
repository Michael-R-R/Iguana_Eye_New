#include "EGridShader.h"

EGridShader::EGridShader(const unsigned long long id) :
    IEShader("", id)
{
    this->setType(RsrcType::Editor);

    vertexSource = "#version 430 core\n\n"
                   "layout (location = 0) in vec3 aPos;\n\n"
                   "out vec4 vColor;\n\n"
                   "void main()\n"
                   "{\n"
                   "\tif(aPos.x == 0.0)\n"
                   "\t\tvColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
                   "\telse if(aPos.y == 0.0)\n"
                   "\t\tvColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                   "\telse\n"
                   "\t\tvColor = vec4(1.0, 1.0, 1.0, 1.0);\n\n"
                   "\tgl_Position = vec4(aPos, 1.0);\n"
                   "}\n";

    fragmentSource = "#version 430 core\n\n"
                     "in vec4 vColor;\n\n"
                     "out vec4 fColor;\n\n"
                     "void main()\n"
                     "{\n"
                     "\tfColor = vColor;\n"
                     "}\n";
}
