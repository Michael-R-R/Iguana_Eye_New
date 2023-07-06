#include "IESerializable.h"

QDataStream& operator<<(QDataStream& out, const IESerializable& obj)
{
    return obj.serialize(out, obj);
}

QDataStream& operator>>(QDataStream& in, IESerializable& obj)
{
    return obj.deserialize(in, obj);
}
