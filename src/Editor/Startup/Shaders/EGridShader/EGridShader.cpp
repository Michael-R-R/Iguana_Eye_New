#include "EGridShader.h"
#include "IEGlslImporter.h"

EGridShader::EGridShader() :
    IEShader("", 0)
{
    IEGlslImporter::importGlsl("./resources/shaders/editor/persp_grid.glsl", *this);
}

EGridShader::~EGridShader()
{

}
