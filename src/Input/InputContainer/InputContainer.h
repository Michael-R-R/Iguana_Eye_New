#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QDataStream>

#include "InputKey.h"

class InputContainer : public QObject
{
    Q_OBJECT

    QMap<QString, InputKey> keys;

public:
    InputContainer(QObject *parent = nullptr);
    ~InputContainer();

    void clear();
    void addValue(const QString name, const InputKey key);
    void removeValue(const QString& name);
    void updateValue(const QString name, const InputKey key);
    InputKey* fetchValue(const QString& name);
    QString fetchKey(const int mod, const int key) const;
    bool doesExist(const QString& name) const;
    bool doesExist(const int mod, const int key) const;

    const QMap<QString, InputKey>& getKeys() const { return keys; } // TODO make this const
    void setKeys(const QMap<QString, InputKey> val) { keys = val;}

signals:
    void cleared();
};

QDataStream& operator<<(QDataStream& out, const InputContainer& container);
QDataStream& operator>>(QDataStream& in, InputContainer& container);
