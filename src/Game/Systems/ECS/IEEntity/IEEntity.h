#pragma once

#include <QDataStream>

class IEEntity
{
    int id;

public:
    IEEntity();
    IEEntity(const int id_);
    IEEntity(const IEEntity& other);
    ~IEEntity() {}

    IEEntity& operator=(const IEEntity& other) { this->id = other.id; return *this; }
    bool operator==(const IEEntity& other) { return this->id == other.id; }
    bool operator!=(const IEEntity& other) { return this->id != other.id; }
    bool operator<(const IEEntity& other) const { return this->id < other.id; }
    bool operator>(const IEEntity& other) const { return this->id > other.id; }

    int getId() const { return id; }

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
