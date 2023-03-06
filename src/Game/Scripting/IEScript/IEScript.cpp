#include "IEScript.h"
#include <QJSEngine>
#include "IEEntity.h"

IEScript::IEScript() :
    filePath(""),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
{

}

IEScript::IEScript(const QString& path) :
    filePath(path),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
{

}

IEScript::IEScript(const IEScript& other) :
    filePath(other.filePath),
    jsAttachEntityFunc(), jsStartFunc(), jsUpdateFunc()
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
