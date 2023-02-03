#include "InputContainer.h"

InputContainer::InputContainer(QObject *parent) :
    QObject(parent),
    keys()
{
    addValue("Invalid", InputKey(-1, -1));
}

InputContainer::~InputContainer()
{

}

void InputContainer::clear()
{
    keys.clear();
    emit cleared();
}

void InputContainer::addValue(const QString name, const InputKey key)
{
    if(doesExist(name)) { return; }
    keys[name] = key;
}

void InputContainer::removeValue(const QString& name)
{
    if(!doesExist(name)) { return; }
    keys.remove(name);
}

void InputContainer::updateValue(const QString name, const InputKey key)
{
    if(!doesExist(name)) { return; }
    keys[name] = key;
}

InputKey* InputContainer::fetchValue(const QString& name)
{
    if(!doesExist(name)) { return &keys["Invalid"]; }
    return &keys[name];
}

QString InputContainer::fetchKey(const int mod, const int key) const
{
    if(!doesExist(mod, key)) { return ""; }
    return keys.key(InputKey(mod, key));
}

bool InputContainer::doesExist(const QString& name) const
{
    return (keys.find(name) != keys.end());
}

bool InputContainer::doesExist(const int mod, const int key) const
{
    return (std::find(keys.begin(), keys.end(), InputKey(mod, key)) != keys.end());
}

QDataStream& operator<<(QDataStream& out, const InputContainer& container)
{
    QMapIterator<QString, InputKey> it(container.getKeys());
    while(it.hasNext())
    {
        it.next();

        out << it.key() << it.value();
    }

    return out;
}

QDataStream& operator>>(QDataStream& in, InputContainer& container)
{
    QMap<QString, InputKey> keys;

    QString tempStr;
    InputKey tempKey;
    while(!in.atEnd())
    {
        in >> tempStr >> tempKey;
        keys[tempStr] = tempKey;
    }

    container.setKeys(keys);

    return in;
}











