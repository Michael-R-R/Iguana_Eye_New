#include "InputContainer.h"

InputContainer::InputContainer(QObject *parent) :
    QObject(parent),
    keys()
{
    addValue("Invalid", new InputKey(-1, -1));
}

InputContainer::~InputContainer()
{
    clear();
}

bool InputContainer::addValue(const QString key, InputKey* value)
{
    if(doesExist(key))
    {
        delete value;
        return false;
    }

    keys[key] = value;

    return true;
}

bool InputContainer::removeValue(const QString& key)
{
    if(!doesExist(key))
        return false;

    auto temp = keys[key];
    keys.remove(key);
    delete temp;

    return true;
}

bool InputContainer::updateValue(const QString& key, const int modVal, const int keyVal)
{
    if(!doesExist(key))
        return false;

    keys[key]->update(modVal, keyVal);

    return true;
}

QString InputContainer::fetchKey(const int mod, const int key) const
{
    auto temp = InputKey(mod, key);

    QMapIterator<QString, InputKey*> it(keys);
    while(it.hasNext())
    {
        it.next();
        if(*it.value() == temp)
        {
            return it.key();
        }
    }

    return "";
}

InputKey* InputContainer::getValue(const QString& key) const
{
    if(!doesExist(key)) { return keys["Invalid"]; }

    return keys[key];
}

bool InputContainer::doesExist(const QString& key) const
{
    return (keys.find(key) != keys.end());
}

bool InputContainer::doesExist(const int mod, const int key) const
{
    auto temp = InputKey(mod, key);

    QMapIterator<QString, InputKey*> it(keys);
    while(it.hasNext())
    {
        it.next();
        if(*it.value() == temp)
        {
            return true;
        }
    }

    return false;
}

void InputContainer::clear()
{
    QMapIterator<QString, InputKey*> it(keys);
    while(it.hasNext())
    {
        it.next();

        auto temp = it.value();
        keys[it.key()] = nullptr;
        delete temp;
    }

    keys.clear();
    emit cleared();
}
