#pragma once

#include <QObject>
#include <QMap>
#include <QString>

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

    QMap<QString, InputKey>& getKeys();

signals:
    void cleared();
};

