#pragma once

#include <QString>

class IEHash
{

public:
    static uint64_t Compute(const QString& str);
};

