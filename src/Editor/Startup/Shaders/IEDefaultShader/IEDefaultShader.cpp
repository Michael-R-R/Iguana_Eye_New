#include "IEDefaultShader.h"
#include "IEGlslImporter.h"

IEDefaultShader::IEDefaultShader(const QString& path) :
    IEShader(path)
{
    IEGlslImporter::importGlsl(path, *this);
}

IEDefaultShader::~IEDefaultShader()
{

}

