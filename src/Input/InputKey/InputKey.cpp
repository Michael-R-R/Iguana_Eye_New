#include "InputKey.h"

InputKey::InputKey(QObject* parent) :
    QObject(parent),
    mod(0), key(0),
    keySequence()
{

}

InputKey::InputKey(int mod_, int key_, QObject* parent) :
    QObject(parent),
    mod(mod_), key(key_),
    keySequence(mod | key)
{

}

InputKey::InputKey(const InputKey& other) :
    QObject(other.parent()),
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
