#include "EGridShader.h"
#include "IEFile.h"
#include "IEGlslImport.h"

EGridShader::EGridShader(QObject* parent) :
    IEShader(parent)
{
    IEGlslImport::importPath(IEFile::absolutePath("./resources/shaders/editor/persp_grid.glsl"), *this);
}

EGridShader::~EGridShader()
{

}
