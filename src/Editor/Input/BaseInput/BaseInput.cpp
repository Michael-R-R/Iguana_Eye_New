#include "BaseInput.h"

BaseInput::BaseInput() :
    inputContainer()
{

}

BaseInput::~BaseInput()
{

}

bool BaseInput::updateConfigKey(const QString& key, const int modVal, const int keyVal)
{
    return inputContainer.updateValue(key, modVal, keyVal);
}

QString BaseInput::getKeyName(const int mod, const int key) const
{
    return inputContainer.getKey(mod, key);
}

InputKey& BaseInput::getConfigKey(const char* key)
{
    return inputContainer.getValue(key);
}

bool BaseInput::doesExist(const int mod, const int key) const
{
    return inputContainer.doesExist(mod, key);
}
