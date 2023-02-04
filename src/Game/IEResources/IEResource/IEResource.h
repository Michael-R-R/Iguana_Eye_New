#pragma once

class IEResource
{
    unsigned long long id;

public:
    IEResource(const unsigned long long id_);
    ~IEResource();

    const unsigned long long getId() const { return id; }
    void setId(const unsigned long long val) { id = val; }
};

