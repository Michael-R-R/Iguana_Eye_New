#pragma once

#include <QDataStream>

class Serializable
{

public:
    Serializable() {}
    ~Serializable() {}

    virtual QDataStream& serialize(QDataStream& out, const Serializable& obj) const = 0;
    virtual QDataStream& deserialize(QDataStream& in, Serializable& obj) const = 0;
};

QDataStream& operator<<(QDataStream& out, const Serializable& obj);
QDataStream& operator>>(QDataStream& in, Serializable& obj);
