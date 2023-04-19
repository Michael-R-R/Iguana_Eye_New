#pragma once

#include <QObject>
#include <QKeySequence>
#include <QDataStream>
#include <QDebug>

#include "Serializable.h"

class InputKey : public QObject, public Serializable
{
    Q_OBJECT

    int mod;
    int key;
    QKeySequence keySequence;

public:
    InputKey();
    InputKey(int mod_, int key_);
    InputKey(const InputKey& other);
    ~InputKey();

    void operator =(const InputKey& other);
    bool operator ==(const InputKey& other) const { return (this->keySequence == other.keySequence); }
    bool operator !=(const InputKey& other) const { return (this->keySequence != other.keySequence); }
    bool operator <=(const InputKey& other) const { return (this->keySequence <= other.keySequence); }
    bool operator >=(const InputKey& other) const { return (this->keySequence >= other.keySequence); }
    bool operator <(const InputKey& other) const { return (this->keySequence < other.keySequence); }
    bool operator >(const InputKey& other) const { return (this->keySequence > other.keySequence); }
    friend QDebug operator<<(QDebug d, const InputKey& key) { d << key.mod << key.key; return d; }

    void update(const int mod, const int key);

    int getMod() const { return mod; }
    int getKey() const { return key; }
    QKeySequence getKeySequence() const { return keySequence; }

signals:
    void updated(const QKeySequence newBinding);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
