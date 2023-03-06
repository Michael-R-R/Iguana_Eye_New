#include "IEGlobalInputScript.h"
#include "IEInput.h"

IEGlobalInputScript::IEGlobalInputScript(IEInput* val, QObject* parent) :
    QObject(parent),
    input(val)
{

}

IEGlobalInputScript::~IEGlobalInputScript()
{
    input = nullptr;
}

bool IEGlobalInputScript::isPressed(const QString& keyName)
{
    return input->isPressed(keyName.toStdString().c_str());
}

