#include "IEEntity.h"

QDataStream& operator<<(QDataStream& out, const IEEntity& entity)
{
    out << entity.getId();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEEntity& entity)
{
    int id;

    in >> id;

    entity.setId(id);

    return in;
}
