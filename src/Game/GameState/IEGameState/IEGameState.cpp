#include "IEGameState.h"

QDataStream& IEGameState::serialize(QDataStream& out, const Serializable&) const
{
    return out;
}

QDataStream& IEGameState::deserialize(QDataStream& in, Serializable&)
{
    return in;
}
