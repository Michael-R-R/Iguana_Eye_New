#include "IEGlslImporter.h"
#include "IEShader.h"
#include "IEFile.h"

bool IEGlslImporter::importGlsl(const QString& path, IEShader* shader)
{
    if(path.lastIndexOf(".glsl") < 0)
        return false;

    QString vSrc = "";
    QString fSrc = "";

    std::tie(vSrc, fSrc) = parseFile(path);
    if(vSrc.isEmpty() || fSrc.isEmpty())
        return false;

    shader->setVertexSrc(vSrc);
    shader->setFragmentSrc(fSrc);

    return true;
}

std::tuple<QString, QString> IEGlslImporter::parseFile(const QString& filePath)
{
    QString content = "";
    if(!IEFile::read(filePath, &content))
        return std::make_tuple("", "");

    if(content.isEmpty())
        return std::make_tuple("", "");

    QString vDelimiter = "[VERTEX]";
    QString fDelimiter = "[FRAGMENT]";

    int vIndex = content.indexOf(vDelimiter);
    int fIndex = content.indexOf(fDelimiter);
    if(vIndex < 0 || fIndex < 0)
        return std::make_tuple("", "");

    int vStart = vIndex + vDelimiter.length() + 1;
    int vEnd = fIndex - vStart;
    QString vSrc = content.mid(vStart, vEnd);

    int fStart = fIndex + fDelimiter.length() + 1;
    QString fSrc = content.mid(fStart);

    return std::make_tuple(vSrc, fSrc);
}
