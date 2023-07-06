#include "InputContainer.h"

InputContainer::InputContainer() :
    QObject(),
    keys()
{
    addValue("Invalid", InputKey(-1, -1));
}

InputContainer::~InputContainer()
{

}

bool InputContainer::addValue(const QString key, InputKey value)
{
    if(doesExist(key))
        return false;

    keys[key] = value;

    return true;
}

bool InputContainer::removeValue(const QString& key)
{
    if(!doesExist(key))
        return false;

    keys.remove(key);

    return true;
}

bool InputContainer::updateValue(const QString& key, const int modVal, const int keyVal)
{
    if(!doesExist(key))
        return false;

    keys[key].update(modVal, keyVal);

    return true;
}

QString InputContainer::getKey(const int mod, const int key) const
{
    auto temp = InputKey(mod, key);

    QHashIterator<QString, InputKey> it(keys);
    while(it.hasNext())
    {
        it.next();
        if(it.value() == temp)
        {
            return it.key();
        }
    }

    return "";
}

InputKey& InputContainer::getValue(const QString& key)
{
    if(!doesExist(key))
        return keys["Invalid"];

    return keys[key];
}

bool InputContainer::doesExist(const QString& key) const
{
    return (keys.find(key) != keys.end());
}

bool InputContainer::doesExist(const int mod, const int key) const
{
    auto temp = InputKey(mod, key);

    QHashIterator<QString, InputKey> it(keys);
    while(it.hasNext())
    {
        it.next();
        if(it.value() == temp)
        {
            return true;
        }
    }

    return false;
}

void InputContainer::clear()
{
    keys.clear();

    emit cleared();
}

QDataStream& InputContainer::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& container = static_cast<const InputContainer&>(obj);

    int size = (int)container.keys.size();
    out << size;

    QHashIterator<QString, InputKey> it(container.keys);
    while(it.hasNext())
    {
        it.next();
        out << it.key() << it.value();
    }

    return out;
}

QDataStream& InputContainer::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& container = static_cast<InputContainer&>(obj);

    int size = 0;
    in >> size;

    container.clear();
    for(int i = 0; i < size; i++)
    {
        QString key = "";
        InputKey value = InputKey();

        in >> key >> value;

        container.keys[key] = value;
    }

    return in;
}
