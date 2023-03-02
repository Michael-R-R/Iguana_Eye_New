#include "EGridShader.h"
#include "IEGlslImporter.h"

EGridShader::EGridShader(const unsigned long long id) :
    IEShader("", id)
{
    this->setType(Type::Editor);

    IEGlslImporter::importGlsl("./resources/shaders/editor/persp_grid.glsl", this);
}
