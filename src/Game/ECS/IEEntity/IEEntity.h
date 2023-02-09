#pragma once

#include <QDataStream>

class IEEntity
{
    int id;

public:
    IEEntity() :
        id(-1) {}

    IEEntity(const int id_) :
        id(id_) {}

    ~IEEntity() {}

    bool operator==(const IEEntity& other) { return this->id == other.id; }
    bool operator!=(const IEEntity& other) { return this->id != other.id; }
    bool operator<(const IEEntity& other) const { return this->id < other.id; }
    bool operator>(const IEEntity& other) const { return this->id > other.id; }

    friend QDataStream& operator<<(QDataStream& out, const IEEntity& entity)
    {
        out << entity.id;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEEntity& entity)
    {
        in >> entity.id;
        return in;
    }
};
