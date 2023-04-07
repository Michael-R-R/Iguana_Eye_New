#include "IEGameSystem.h"

QDataStream& IEGameSystem::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEGameSystem::deserialize(QDataStream& in, Serializable&)
{
    return in;
}
