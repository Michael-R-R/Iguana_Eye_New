#pragma once

#include <QDataStream>

class IEEntity
{
    int id;

public:
    IEEntity(const int id_) :
        id(id_) {}

    ~IEEntity() {}

    bool operator==(const IEEntity& other) { return this->id == other.id; }
    bool operator!=(const IEEntity& other) { return this->id != other.id; }
    bool operator<(const IEEntity& other) { return this->id < other.id; }
    bool operator>(const IEEntity& other) { return this->id > other.id; }

    int getId() const { return id; }
    void setId(const int val) { id = val; }
};

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
