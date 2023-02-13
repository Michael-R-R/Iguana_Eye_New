#pragma once

class IEResource
{
protected:
    unsigned long long id;

public:
    IEResource(const unsigned long long id_);
    ~IEResource();

    bool operator==(const IEResource& other) { return (this->id == other.id); }
    bool operator!=(const IEResource& other) { return (this->id != other.id); }
    bool operator<(const IEResource& other) { return (this->id < other.id); }
    bool operator>(const IEResource& other) { return (this->id > other.id); }

    const unsigned long long getId() const { return id; }
    void setId(const unsigned long long val) { id = val; }
};

