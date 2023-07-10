#include "IEGlslImport.h"
#include "IEShader.h"
#include "IEFile.h"
#include "GLInclude.h"

bool IEGlslImport::importPath(const QString& path, IEShader& shader)
{
    if(path.lastIndexOf(".glsl") < 0)
        return false;

    QString vSrc = "";
    QString fSrc = "";

    std::tie(vSrc, fSrc) = parseFile(path);
    if(vSrc.isEmpty() || fSrc.isEmpty())
        return false;

    processIncludes(vSrc);
    processIncludes(fSrc);

    shader.updateId(convertPath(path));
    shader.setVertexSrc(vSrc);
    shader.setFragmentSrc(fSrc);

    return shader.build();
}

bool IEGlslImport::importPath(const QString& path, QString& vSrc, QString& fSrc)
{
    if(path.lastIndexOf(".glsl") < 0)
        return false;

    QString tempVSrc = "";
    QString tempFSrc = "";

    std::tie(tempVSrc, tempFSrc) = parseFile(path);
    if(tempVSrc.isEmpty() || tempFSrc.isEmpty())
        return false;

    vSrc = tempVSrc;
    fSrc = tempFSrc;

    return true;
}

QString IEGlslImport::convertPath(const QString& path)
{
    QString newPath = path;
    QString extension = IEFile::extractExtension(path);

    return newPath.replace(extension, ".ieshader");
}

std::tuple<QString, QString> IEGlslImport::parseFile(const QString& filePath)
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

void IEGlslImport::processIncludes(QString& src)
{
    src.replace("#include uVP", GLInclude::includeViewProjection());
    src.replace("#include uCamera", GLInclude::includeCamera());
    src.replace("#include uDirLight", GLInclude::includeDirLight());
    src.replace("#include uPointLight", GLInclude::includePointLight());
    src.replace("#include uSpotLight", GLInclude::includeSpotLight());
}
