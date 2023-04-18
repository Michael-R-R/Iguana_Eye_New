#include "EGridShader.h"
#include "IEGlslImporter.h"

EGridShader::EGridShader(QObject* parent) :
    IEShader(parent)
{
    IEGlslImporter::importGlsl("./resources/shaders/editor/persp_grid.glsl", *this);
}

EGridShader::~EGridShader()
{

}
