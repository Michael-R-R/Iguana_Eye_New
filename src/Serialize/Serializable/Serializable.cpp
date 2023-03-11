#include "Serializable.h"

QDataStream& operator<<(QDataStream& out, const Serializable& obj)
{
    return obj.serialize(out, obj);
}

QDataStream& operator>>(QDataStream& in, Serializable& obj)
{
    return obj.deserialize(in, obj);
}
