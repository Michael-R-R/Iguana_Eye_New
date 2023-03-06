#include "IELocalEntityScript.h"

IELocalEntityScript::IELocalEntityScript(const int val, QObject* parent) :
    QObject(parent),
    entityId(val)
{

}
