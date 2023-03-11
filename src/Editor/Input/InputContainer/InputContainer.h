#pragma once

#include <QObject>
#include <QMap>
#include <QString>

#include "InputKey.h"
#include "Serializable.h"

class InputContainer : public QObject, public Serializable
{
    Q_OBJECT

    QMap<QString, InputKey> keys;

public:
    InputContainer();
    ~InputContainer();

    bool addValue(const QString key, InputKey value);
    bool removeValue(const QString& key);
    bool updateValue(const QString& key, const int modVal, const int keyVal);
    QString getKey(const int mod, const int key) const;
    InputKey& getValue(const QString& key);
    bool doesExist(const QString& key) const;
    bool doesExist(const int mod, const int key) const;
    void clear();

    const QMap<QString, InputKey>& getKeys() const { return keys; }
    void setKeys(const QMap<QString, InputKey>& val) { keys = val; }

signals:
    void cleared();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
