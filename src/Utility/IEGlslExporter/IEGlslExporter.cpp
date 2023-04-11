#include "IEGlslExporter.h"
#include "IEFile.h"

bool IEGlslExporter::exportGlsl(const QString& path, const QString& vSrc, const QString& fSrc)
{
    if(path.isEmpty())
        return false;

    QString content = QString("[VERTEX]\n%1\n[FRAGMENT]\n%2").arg(vSrc, fSrc);

    return IEFile::write(path, content);
}
