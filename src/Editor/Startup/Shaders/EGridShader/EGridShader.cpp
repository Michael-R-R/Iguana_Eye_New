#include "EGridShader.h"
#include "IEShaderImport.h"

EGridShader::EGridShader(QObject* parent) :
    IEShader(parent)
{
    IEShaderImport::importShader("./resources/shaders/editor/persp_grid.glsl", *this);
}

EGridShader::~EGridShader()
{

}
