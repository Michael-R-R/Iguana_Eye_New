#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QDataStream>

#include "InputKey.h"

class InputContainer : public QObject
{
    Q_OBJECT

    QMap<QString, InputKey*> keys;

public:
    InputContainer(QObject *parent = nullptr);
    ~InputContainer();

    bool addValue(const QString key, InputKey* value);
    bool removeValue(const QString& key);
    bool updateValue(const QString& key, const int modVal, const int keyVal);
    QString fetchKey(const int mod, const int key) const;
    InputKey* fetchValue(const QString& key) const;
    bool doesExist(const QString& key) const;
    bool doesExist(const int mod, const int key) const;
    void clear();

    const QMap<QString, InputKey*>& getKeys() const { return keys; }
    void setKeys(const QMap<QString, InputKey*>& val) { keys = val; }

signals:
    void cleared();

public:
    friend QDataStream& operator<<(QDataStream& out, const InputContainer& container)
    {
        int size = (int)container.keys.size();
        out << size;

        QMapIterator<QString, InputKey*> it(container.keys);
        while(it.hasNext())
        {
            it.next();
            out << it.key() << *it.value();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, InputContainer& container)
    {
        int size = 0;
        in >> size;

        QString key = "";
        InputKey* value = nullptr;

        container.clear();
        for(int i = 0; i < size; i++)
        {
            value = new InputKey();

            in >> key >> *value;

            container.keys[key] = value;
        }

        return in;
    }
};
