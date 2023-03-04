#include "IEScript.h"

IEScript::IEScript() :
    IEResource("", 0)
{

}

IEScript::IEScript(const QString& path, const unsigned long long resourceId) :
    IEResource(path, resourceId)
{

}

IEScript::IEScript(const IEScript& other) :
    IEResource(other.filePath, other.id)
{

}
