#include "BaseInput.h"

BaseInput::BaseInput(QObject* parent) :
    IEObject(parent),
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

QDataStream& BaseInput::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& input = static_cast<const BaseInput&>(obj);

    out << input.inputContainer;

    return out;
}

QDataStream& BaseInput::deserialize(QDataStream& in, Serializable& obj)
{
    auto& input = static_cast<BaseInput&>(obj);

    in >> input.inputContainer;

    return in;
}
