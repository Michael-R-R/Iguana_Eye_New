#include "IEShaderExport.h"
#include "IEFile.h"

bool IEShaderExport::exportShader(const QString& path, const QString& vSrc, const QString& fSrc)
{
    if(path.isEmpty())
        return false;

    QString content = QString("[VERTEX]\n%1[FRAGMENT]\n%2").arg(vSrc, fSrc);

    return IEFile::write(path, content);
}
