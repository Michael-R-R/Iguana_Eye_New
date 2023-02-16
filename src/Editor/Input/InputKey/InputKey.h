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

signals:
    void updated(const QKeySequence newBinding);

public:
    friend QDataStream& operator<<(QDataStream& out, const InputKey& input)
    {
        out << input.mod << input.key;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, InputKey& input)
    {
        in >> input.mod >> input.key;

        input.keySequence = QKeySequence(input.mod | input.key);

        return in;
    }
};
