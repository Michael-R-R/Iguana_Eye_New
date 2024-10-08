#pragma once

#include <QObject>
#include <QHash>
#include <QString>

#include "InputKey.h"
#include "IESerializable.h"

class InputContainer : public QObject, public IESerializable
{
    Q_OBJECT

    QHash<QString, InputKey> keys;

public:
    InputContainer();
    virtual ~InputContainer();

    bool addValue(const QString key, InputKey value);
    bool removeValue(const QString& key);
    bool updateValue(const QString& key, const int modVal, const int keyVal);
    QString getKey(const int mod, const int key) const;
    InputKey& getValue(const QString& key);
    bool doesExist(const QString& key) const;
    bool doesExist(const int mod, const int key) const;
    void clear();

    const QHash<QString, InputKey>& getKeys() const { return keys; }
    void setKeys(const QHash<QString, InputKey>& val) { keys = val; }

signals:
    void cleared();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
