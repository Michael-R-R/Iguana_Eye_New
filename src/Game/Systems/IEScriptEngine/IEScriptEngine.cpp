#include "IEScriptEngine.h"
#include "IEGlobalTimeScript.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEObject(parent),
    engine(new QJSEngine(this)),
    globalTime(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    globalTime = new IEGlobalTimeScript(event, this);
    engine->globalObject().setProperty("IETime", engine->newQObject(globalTime));

    engine->installExtensions(QJSEngine::ConsoleExtension);

    // TODO test
    script = IEScript("./resources/scripts/test.js", 0);
}

void IEScriptEngine::shutdown()
{

}

void IEScriptEngine::onUpdateFrame()
{
    // TODO get all scripts and call update()

    // TODO test
    for(int i = 0; i < 100; i++)
    {
        QJSValue val = script.call(engine);
        if(val.isError())
        {
            QString error = QString("Exception at line %1:\nMessage: %2\nStack: %3\n")
                    .arg(val.property("lineNumber").toString(),
                         val.toString(),
                         val.property("stack").toString());

            qDebug() << error;
        }
    }
}
