#include "EGridShader.h"
#include "IEFile.h"
#include "IEGlslImport.h"

EGridShader::EGridShader(QObject* parent) :
    IEShader(parent)
{
    QString path = IEFile::absolutePath("./resources/scene/global/shaders/editor_grid.glsl");
    IEGlslImport::importPath(path, *this);
}

EGridShader::~EGridShader()
{

}
