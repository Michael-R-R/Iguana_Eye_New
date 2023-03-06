#include "IEScript.h"
#include <QJSEngine>
#include "IEEntity.h"

IEScript::IEScript() :
    IEResource("", 0),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
{

}

IEScript::IEScript(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
{

}

IEScript::IEScript(const IEScript& other) :
    IEResource(other.filePath, other.id),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
{

}

IEScript::~IEScript()
{

}

void IEScript::import(QJSEngine* engine)
{
    QJSValue module = engine->importModule(filePath);
    jsAttachEntityFunc = module.property("attachEntity");
    jsStartFunc = module.property("start");
    jsUpdateFunc = module.property("update");
}

QJSValue IEScript::attachEntity(const IEEntity entity)
{
    QJSValueList args;
    args << entity.getId();

    return jsAttachEntityFunc.call(args);
}

QJSValue IEScript::start()
{
    return jsStartFunc.call();
}

QJSValue IEScript::update()
{
    return jsUpdateFunc.call();
}
