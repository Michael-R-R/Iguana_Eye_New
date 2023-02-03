#pragma once

#include <QObject>
#include <QKeySequence>
#include <QDataStream>

class InputKey : public QObject
{
    Q_OBJECT

    int mod;
    int key;
    QKeySequence keySequence;

public:
    InputKey(QObject* parent = nullptr);
    InputKey(int mod_, int key_, QObject* parent = nullptr);
    InputKey(const InputKey& other);
    ~InputKey();

    void operator =(const InputKey& other);
    bool operator ==(const InputKey& other) const { return (this->keySequence == other.keySequence); }
    bool operator !=(const InputKey& other) const { return (this->keySequence != other.keySequence); }
    bool operator <=(const InputKey& other) const { return (this->keySequence <= other.keySequence); }
    bool operator >=(const InputKey& other) const { return (this->keySequence >= other.keySequence); }
    bool operator <(const InputKey& other) const { return (this->keySequence < other.keySequence); }
    bool operator >(const InputKey& other) const { return (this->keySequence > other.keySequence); }

    void update(const int mod, const int key);

    int getMod() const { return mod; }
    int getKey() const { return key; }
    QKeySequence getKeySequence() const { return keySequence; }

    void setMod(const int val) { mod = val; }
    void setKey(const int val) { key = val; }
    void setKeySequence(const QKeySequence val) { keySequence = val; }

signals:
    void updated(const QKeySequence newBinding);
};

QDataStream& operator<<(QDataStream& out, const InputKey& key);
QDataStream& operator>>(QDataStream& in, InputKey& key);
