#include "InputKey.h"

InputKey::InputKey() :
    QObject(),
    mod(0), key(0),
    keySequence()
{

}

InputKey::InputKey(int mod_, int key_) :
    QObject(),
    mod(mod_), key(key_),
    keySequence(mod | key)
{

}

InputKey::InputKey(const InputKey& other) :
    QObject(),
    mod(other.mod), key(other.key),
    keySequence(other.keySequence)
{

}

InputKey::~InputKey()
{

}

void InputKey::operator=(const InputKey& other)
{
    mod = other.mod;
    key = other.key;

    keySequence = QKeySequence(mod | key);
}

void InputKey::update(const int mod, const int key)
{
    this->mod = mod;
    this->key = key;

    keySequence = QKeySequence(mod | key);

    emit updated(keySequence);
}

QDataStream& InputKey::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& input = static_cast<const InputKey&>(obj);

    out << input.mod << input.key;

    return out;
}

QDataStream& InputKey::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& input = static_cast<InputKey&>(obj);

    in >> input.mod >> input.key;

    input.keySequence = QKeySequence(input.mod | input.key);

    return in;
}
