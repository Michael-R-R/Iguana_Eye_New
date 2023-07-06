#include "IESystem.h"

QDataStream& IESystem::serialize(QDataStream& out, const IESerializable&) const
{
    return out;
}

QDataStream& IESystem::deserialize(QDataStream& in, IESerializable&)
{
    return in;
}
