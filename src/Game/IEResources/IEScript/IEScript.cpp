#include "IEScript.h"
#include <QJSEngine>
#include "IEFile.h"

IEScript::IEScript() :
    IEResource("", 0),
    code("")
{

}

IEScript::IEScript(const QString& path, const unsigned long long resourceId) :
    IEResource(path, resourceId),
    code("")
{
    QString src = "";
    IEFile::read(path, &src);

    code = QString("(function() { %1\n })()").arg(src);
}

IEScript::IEScript(const IEScript& other) :
    IEResource(other.filePath, other.id),
    code(other.code)
{

}

QJSValue IEScript::call(QJSEngine* engine)
{
    return engine->evaluate(code, filePath);
}
