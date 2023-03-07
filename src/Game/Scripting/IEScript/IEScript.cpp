#include "IEScript.h"
#include "IEEntity.h"

IEScript::IEScript() :
    IEResource("", 0)
{

}

IEScript::IEScript(const QString& path, const unsigned long long id) :
    IEResource(path, id)
{

}

IEScript::IEScript(const IEScript& other) :
    IEResource(other.filePath, other.id)
{

}

IEScript::~IEScript()
{

}

void IEScript::attachEntity(const IEEntity)
{
}

void IEScript::start()
{
}

void IEScript::update()
{
}
