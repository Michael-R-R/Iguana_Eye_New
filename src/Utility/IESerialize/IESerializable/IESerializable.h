#pragma once

#include <QDataStream>

class IESerializable
{

public:
    IESerializable() {}
    virtual ~IESerializable() {}

    virtual QDataStream& serialize(QDataStream& out, const IESerializable& obj) const = 0;
    virtual QDataStream& deserialize(QDataStream& in, IESerializable& obj) = 0;

    friend QDataStream& operator<<(QDataStream& out, const IESerializable& obj);
    friend QDataStream& operator>>(QDataStream& in, IESerializable& obj);
};
